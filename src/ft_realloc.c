/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvannest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 16:24:46 by gvannest          #+#    #+#             */
/*   Updated: 2020/01/27 17:50:34 by cpaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

static void		*ft_realloc_dispatch(void *ptr, size_t size_aligned,
		t_heapheader *cur_heap, size_t size_wo_flags)
{
	char			heap_type;
	size_t			chk_s;
	t_chunk			*next_chunk;

	chk_s = size_wo_flags - HDR_SIZE;
	next_chunk = ptr + size_wo_flags;
	if (!(heap_type = ft_is_same_heap_size(size_wo_flags, size_aligned)))
		ptr = ft_new_alloc(ptr + HDR_SIZE, size_aligned, chk_s);
	else if (size_aligned + HDR_SIZE <= size_wo_flags)
		ptr = ft_reduce_chunk(ptr, size_aligned + HDR_SIZE, size_wo_flags,
				heap_type);
	else if (!(cur_heap->current_footer)
			|| (void*)next_chunk >= cur_heap->current_footer)
		ptr = ft_new_alloc(ptr + HDR_SIZE, size_aligned, chk_s);
	else if (!(next_chunk->mchunk_size & F_FLAG))
		ptr = ft_new_alloc(ptr + HDR_SIZE, size_aligned, chk_s);
	else if (ft_size_wo_flags(next_chunk->mchunk_size) >
			size_aligned + HDR_SIZE)
		ptr = ft_next_chunk_free(ptr, (t_chunk *)next_chunk, size_aligned,
		cur_heap);
	else
		ptr = ft_new_alloc(ptr + HDR_SIZE, size_aligned, chk_s);
	return (ptr);
}

void			*ft_realloc(void *ptr, size_t size)
{
	size_t			size_wo_flags;
	t_heapheader	*current_heap;
	size_t			size_al;

	if (!ptr)
		return (ft_malloc(size));
	if (ptr && !size)
	{
		ft_free(ptr);
		return (ft_malloc(0));
	}
	ptr = ptr - HDR_SIZE;
	if (!(control_ptr(ptr)) || ((t_chunk*)ptr)->mchunk_size & F_FLAG)
	{
		ft_free(ptr);
		return (NULL);
	}
	size_al = align_size(size);
	current_heap = find_current_heap(ptr);
	size_wo_flags = ft_size_wo_flags(((t_chunk*)ptr)->mchunk_size);
	return (ft_realloc_dispatch(ptr, size_al, current_heap, size_wo_flags));
}

void			*realloc(void *ptr, size_t size)
{
	void			*new_ptr;

	pthread_mutex_lock(&g_mutex);
	new_ptr = ft_realloc(ptr, size);
	pthread_mutex_unlock(&g_mutex);
	return (new_ptr);
}
