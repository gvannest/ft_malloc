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

	new_ptr = malloc(size);
	ft_memcpy(new_ptr, ptr, old_size - HDR_SIZE_ALLOC);
	free(ptr);
	return new_ptr;
}

static void *ft_move_free_header(void *ptr, size_t chunk_size, size_t size_diff)
{
	size_t flags;
	size_t current_free_size;
	void *free_block;

	free_block = ptr + chunk_size;
	current_free_size = ft_size_wo_flags(((t_freechunk *)free_block)->mchunk_size);
	flags = ft_flags(((t_freechunk *)free_block)->mchunk_size);
	ft_memcpy(free_block + size_diff, free_block, HDR_SIZE_FREE);
	set_size((current_free_size - size_diff) | flags, free_block + size_diff);
	set_prev_size(((t_freechunk *)free_block)->mchunk_prevsize + size_diff, free_block + size_diff);
	return (free_block + size_diff);
}

static void ft_update_current_size(void *ptr, size_t new_size)
{
	set_size(new_size | ft_flags(((t_allocchunk *)ptr)->mchunk_size), ptr);
}

static void ft_update_chunk_after_free(void *prev_ptr, size_t new_size, char prev_is_free)
{
	size_t size;

	size = ((t_allocchunk *)(prev_ptr + new_size))->mchunk_size;
	if (!prev_is_free)
	{
		size = size & ~P_FLAG;
		set_size(size, prev_ptr + new_size);
	}
	set_prev_size(new_size, prev_ptr + new_size);
}

static void *ft_next_chunk_free(void *ptr, t_freechunk *next_chunk, size_t size_user, size_t size_wo_flags)
{
	size_t size_diff;
	size_t next_size_wo_flags;
	void *free_chunk;

	next_size_wo_flags = ft_size_wo_flags(next_chunk->mchunk_size);
	size_diff = size_user - (size_wo_flags - HDR_SIZE_ALLOC);
	if ((int)next_size_wo_flags - (int)size_diff >= 0)
	{
		if ((int)next_size_wo_flags - (int)size_diff < HDR_SIZE_FREE)
		{
			ft_del_free_list(next_chunk);
			ft_update_current_size(ptr, size_wo_flags + next_size_wo_flags);
			ft_update_chunk_after_free(ptr, size_wo_flags + next_size_wo_flags, 0);
		}
		else
		{
			free_chunk = ft_move_free_header(ptr, size_wo_flags, size_diff);
			ft_update_current_size(ptr, size_wo_flags + size_diff);
			ft_update_chunk_after_free(free_chunk, next_size_wo_flags - size_diff, 1);
			update_freelist(((t_freechunk*)free_chunk)->prev_freechunk, (t_freechunk*)free_chunk, ((t_freechunk*)free_chunk)->next_freechunk);
		}
		return (ptr + HDR_SIZE_ALLOC);
	}
	return (ft_new_alloc(ptr + HDR_SIZE_ALLOC, size_user, size_wo_flags));
}

static char ft_is_same_heap_size(size_t size_chunk, size_t size_user)
{
	if (size_chunk < TINY_MAX_SIZE && size_user < TINY_MAX_SIZE)
		return 1;
	if ((size_chunk < SMALL_MAX_SIZE && size_user < SMALL_MAX_SIZE) && (size_chunk >= TINY_MAX_SIZE && size_user >= TINY_MAX_SIZE))
		return 2;
	return (0);
}


static void	*ft_reduce_chunk(void *ptr, size_t size_user, size_t size_wo_flags, char heap_type)
{
	size_t	size_diff;
	void	**begin_free;
	
	size_diff = size_wo_flags - size_user;
	begin_free = heap_type == 1 ? &(g_ptr.tiny_free_begin) : &(g_ptr.small_free_begin); 
	if (size_user == size_wo_flags || size_diff < HDR_SIZE_FREE)
		return ptr;
	create_new_free_chunk(begin_free, ptr, size_user, find_current_heap(ptr));
	return (ptr);
}

void *realloc(void *ptr, size_t size)
{
	t_allocchunk	*next_chunk;
	size_t			size_wo_flags;
	size_t			size_aligned;
	char			heap_type;
	t_heapheader	*current_heap;

	current_heap = find_current_heap(ptr);
	if (!ptr)
		return malloc(size);
	if (ptr && !size)
	{
		free(ptr);
		return NULL;
	}
	if(!((ptr > (void*)current_heap) && (ptr < current_heap->current_footer)))
		return ptr;
	ptr = ptr - HDR_SIZE_ALLOC;
	size_aligned = align_size(size);
	size_wo_flags = ft_size_wo_flags(((t_allocchunk *)ptr)->mchunk_size);
	if (!ptr || (ptr && ((t_allocchunk*)ptr)->mchunk_size & F_FLAG))
		return NULL;
	if (!(heap_type = ft_is_same_heap_size(size_wo_flags, size_aligned)))
		return ft_new_alloc(ptr + HDR_SIZE_ALLOC, size_aligned, size_wo_flags);
	if (size_aligned <= size_wo_flags)
		return ft_reduce_chunk(ptr, size_aligned, size_wo_flags, heap_type);
//	if (size_wo_flags - HDR_SIZE_ALLOC >= size_aligned)
//		return (ptr + HDR_SIZE_ALLOC);
	next_chunk = ptr + size_wo_flags;
	if (next_chunk == find_current_heap(ptr)->current_footer)
		return ft_new_alloc(ptr + HDR_SIZE_ALLOC, size_aligned, size_wo_flags);
	if (!(next_chunk->mchunk_size & F_FLAG))
		return ft_new_alloc(ptr + HDR_SIZE_ALLOC, size_aligned, size_wo_flags);
	return ft_next_chunk_free(ptr, (t_freechunk *)next_chunk, size_aligned, size_wo_flags);
}
