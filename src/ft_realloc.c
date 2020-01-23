/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvannest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 14:17:08 by gvannest          #+#    #+#             */
/*   Updated: 2020/01/11 18:17:00 by gvannest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

static void *ft_new_alloc(void *ptr, size_t size, size_t old_size)
{
	void *new_ptr;

	old_size = old_size > size ? size : old_size;
	if (!(new_ptr = malloc(size)))
		return NULL;
	ft_memcpy(new_ptr, ptr, old_size);
	free(ptr);
	return new_ptr;
}

static void *ft_move_free_header(void *ptr, size_t chunk_size, size_t size_diff)
{
	size_t flags;
	size_t current_free_size;
	void *free_block;
	t_chunk	free_tmp;

	free_block = ptr + chunk_size;
	current_free_size = ft_size_wo_flags(((t_chunk *)free_block)->mchunk_size);
	flags = ft_flags(((t_chunk *)free_block)->mchunk_size);
	free_tmp = *((t_chunk*)free_block);
	*((t_chunk*)(free_block + size_diff)) = free_tmp;
	set_size((current_free_size - size_diff) | flags, free_block + size_diff);
	set_prev_size(((t_chunk *)free_block)->mchunk_prevsize + size_diff, free_block + size_diff);

	return (free_block + size_diff);
}

static void ft_update_current_size(void *ptr, size_t new_size)
{
	set_size(new_size | ft_flags(((t_chunk*)ptr)->mchunk_size), ptr);
}

static void ft_update_chunk_after_free(void *prev_ptr, size_t new_size, char prev_is_free, t_heapheader *current_heap)
{
	size_t size;

	if (prev_ptr + new_size >= current_heap->current_footer)
		return;
	size = ((t_chunk*)(prev_ptr + new_size))->mchunk_size;
	if (!prev_is_free)
	{
		size = size & ~P_FLAG;
		set_size(size, prev_ptr + new_size);
	}
	set_prev_size(ft_size_wo_flags(new_size), prev_ptr + new_size);
}

static void *ft_next_chunk_free(void *ptr, t_chunk *next_chunk, size_t size_user, size_t size_wo_flags, t_heapheader *current_heap)
{
	size_t size_diff;
	size_t next_size_wo_flags;
	void *free_chunk;

	next_size_wo_flags = ft_size_wo_flags(next_chunk->mchunk_size);
	size_diff = size_user - (size_wo_flags - HDR_SIZE);
	if (next_size_wo_flags >= size_diff)
	{
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
	return (ft_new_alloc(ptr + HDR_SIZE, size_user, size_wo_flags - HDR_SIZE));
}

static char ft_is_same_heap_size(size_t size_chunk, size_t size_user)
{
	if (size_chunk < TINY_MAX_SIZE && size_user < TINY_MAX_SIZE)
		return 1;
	if ((size_chunk < SMALL_MAX_SIZE && size_user < SMALL_MAX_SIZE) && (size_chunk >= TINY_MAX_SIZE && size_user >= TINY_MAX_SIZE))
		return 2;
	return (0);
}


static void	*ft_reduce_chunk(void *ptr, size_t new_chunk_size, size_t actual_size, char heap_type)
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

void *realloc(void *ptr, size_t size)
{
	t_chunk	*next_chunk;
	size_t			size_wo_flags;
	size_t			size_aligned;
	char			heap_type;
	t_heapheader	*current_heap;

	if (!ptr)
		return malloc(size);
	if (ptr && !size)
	{
		free(ptr);
		return NULL;
	}
	ptr = ptr - HDR_SIZE;
	current_heap = find_current_heap(ptr);
	if(!current_heap || !((ptr > (void*)current_heap) && (ptr < current_heap->current_footer)))
		return (ptr + HDR_SIZE);
	size_aligned = align_size(size);
	size_wo_flags = ft_size_wo_flags(((t_chunk*)ptr)->mchunk_size);
	if (!ptr || (ptr && ((t_chunk*)ptr)->mchunk_size & F_FLAG))
		return NULL;
	if (!(heap_type = ft_is_same_heap_size(size_wo_flags, size_aligned)))
		return ft_new_alloc(ptr + HDR_SIZE, size_aligned, size_wo_flags - HDR_SIZE);
	if (size_aligned + HDR_SIZE <= size_wo_flags)
		return ft_reduce_chunk(ptr, size_aligned + HDR_SIZE, size_wo_flags, heap_type);
	next_chunk = ptr + size_wo_flags;
	if (!(current_heap->current_footer) || current_heap->current_footer < (void*)next_chunk)
		return ft_new_alloc(ptr + HDR_SIZE, size_aligned, size_wo_flags - HDR_SIZE);
	if (!(next_chunk->mchunk_size & F_FLAG))
		return ft_new_alloc(ptr + HDR_SIZE, size_aligned, size_wo_flags - HDR_SIZE);
	return ft_next_chunk_free(ptr, (t_chunk *)next_chunk, size_aligned, size_wo_flags, current_heap);
}
