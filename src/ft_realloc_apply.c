/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc_apply.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvannest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 16:36:40 by gvannest          #+#    #+#             */
/*   Updated: 2020/01/25 16:37:20 by gvannest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void		*ft_new_alloc(void *ptr, size_t size, size_t old_size)
{
	void		*new_ptr;

	old_size = old_size > size ? size : old_size;
	if (!(new_ptr = ft_malloc(size)))
		return NULL;
	ft_memcpy(new_ptr, ptr, old_size);
	ft_free(ptr);
	return new_ptr;
}

void		*ft_next_chunk_free(void *ptr, t_chunk *next_chunk, size_t size_user, size_t size_wo_flags, t_heapheader *current_heap)
{
	size_t size_diff;
	size_t next_size_wo_flags;
	void *free_chunk;

	next_size_wo_flags = ft_size_wo_flags(next_chunk->mchunk_size);
	size_diff = size_user - (size_wo_flags - HDR_SIZE);
	if (next_size_wo_flags < size_diff + HDR_SIZE)
	{
		ft_remove_from_list(next_chunk);
		ft_update_current_size(ptr, size_wo_flags + next_size_wo_flags);
		ft_update_chunk_after_free(ptr, size_wo_flags + next_size_wo_flags, 0, current_heap);
	}
	else
	{
		free_chunk = ft_move_free_header(ptr, size_wo_flags, size_diff);
		ft_update_current_size(ptr, size_wo_flags + size_diff);
		ft_update_chunk_after_free(free_chunk, next_size_wo_flags - size_diff, 1, current_heap);
		update_freelist(((t_chunk*)free_chunk)->prev_chunk, (t_chunk*)free_chunk, ((t_chunk*)free_chunk)->next_chunk);
	}
	return (ptr + HDR_SIZE);
}

void		*ft_reduce_chunk(void *ptr, size_t new_chunk_size, size_t actual_size, char heap_type)
{
	size_t	size_reduction;
	void	**begin_free;

	size_reduction = actual_size - new_chunk_size;
	begin_free = heap_type == 1 ? &(g_ptr.tiny_free_begin) : &(g_ptr.small_free_begin); 
	if (new_chunk_size == actual_size || size_reduction < HDR_SIZE)
		return (ptr + HDR_SIZE);
	create_new_free_chunk(begin_free, ptr, new_chunk_size, find_current_heap(ptr));
	return (ptr + HDR_SIZE);
}

