/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvannest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 16:24:46 by gvannest          #+#    #+#             */
/*   Updated: 2020/01/25 17:08:27 by gvannest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

static void		*ft_realloc_dispatch(void *ptr, size_t size_aligned,
		t_heapheader *cur_heap, size_t size_wo_flags)
{
	char			heap_type;
	size_t			chk_s;
	void			*ptr;

	chk_s = size_wo_flags - HDR_SIZE;
	next_chunk = ptr + size_wo_flags;
	ptr = NULL;
	if (!(heap_type = ft_is_same_heap_size(size_wo_flags, size_aligned)))
		ptr = ft_new_alloc(ptr + HDR_SIZE, size_aligned, chk_s);
	else if (size_aligned + HDR_SIZE <= size_wo_flags)
		ptr = ft_reduce_chunk(ptr, size_aligned + HDR_SIZE, size_wo_flags,
				heap_type);
	else if (!(current_heap->current_footer)
			|| (void*)next_chunk >= current_heap->current_footer)
		ptr = ft_new_alloc(ptr + HDR_SIZE, size_aligned, chk_s);
	else if (!(next_chunk->mchunk_size & F_FLAG))
		ptr = ft_new_alloc(ptr + HDR_SIZE, size_aligned, chk_s);
	else if (ft_size_wo_flags(next_chunk->mchunk_size) >
			size_aligned + HDR_SIZE)
		ptr = ft_next_chunk_free(ptr, (t_chunk *)next_chunk, size_aligned,
				size_wo_flags, current_heap);
	else
		ptr = ft_new_alloc(ptr + HDR_SIZE, size_aligned, chk_s);
	return (ptr);
}

void			*ft_realloc(void *ptr, size_t size)
{
	t_chunk			*next_chunk;
	size_t			size_wo_flags;
	t_heapheader	*current_heap;
	size_t			size_al;

	if (!ptr)
		return (ft_malloc(size));
	if (ptr && !size)
	{
		ft_free(ptr);
		return (NULL);
	}
	size_al = align_size(size);
	ptr = ptr - HDR_SIZE;
	current_heap = find_current_heap(ptr);
	size_wo_flags = ft_size_wo_flags(((t_chunk*)ptr)->mchunk_size);
	if (!current_heap || !((ptr > (void*)current_heap) &&
				(ptr < current_heap->current_footer)))
		return (ptr + HDR_SIZE);
	if (!ptr || (ptr && ((t_chunk*)ptr)->mchunk_size & F_FLAG))
		return (NULL);
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
