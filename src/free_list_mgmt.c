/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_list_mgmt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvannest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 14:50:28 by gvannest          #+#    #+#             */
/*   Updated: 2020/01/25 14:54:01 by gvannest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void			ft_first_free_chunk(void *ptr, size_t size, t_chunk *prev_chk)
{
	t_chunk chunk;

	chunk.mchunk_prevsize = 0;
	chunk.mchunk_size = ft_add_flags_to_size(size, 1, 0, 0);
	chunk.prev_chunk = prev_chk;
	if (prev_chk)
		chunk.next_chunk = prev_chk->next_chunk;
	else
		chunk.next_chunk = NULL;
	*(t_chunk*)ptr = chunk;
}

static void		ft_add_free_block(void *ptr, t_chunk *prev_chk,
		t_chunk *next_chk)
{
	t_chunk		chunk;

	chunk.mchunk_prevsize = ((t_chunk*)ptr)->mchunk_prevsize;
	chunk.mchunk_size = (((t_chunk*)ptr)->mchunk_size) | F_FLAG;
	chunk.prev_chunk = prev_chk;
	chunk.next_chunk = next_chk;
	*(t_chunk*)ptr = chunk;
}

static void		ft_insert_list(void *ptr, void **begin_free)
{
	t_chunk		*prev_free;
	t_chunk		*next_free;

	prev_free = ft_find_prev(ptr, (t_chunk*)(*begin_free));
	next_free = NULL;
	if (*begin_free > ptr)
	{
		ft_add_free_block(ptr, NULL, *begin_free);
		((t_chunk*)(*begin_free))->prev_chunk = (t_chunk*)ptr;
		*begin_free = ptr;
	}
	else
	{
		next_free = prev_free->next_chunk;
		ft_add_free_block(ptr, prev_free, next_free);
		update_freelist(prev_free, ptr, next_free);
	}
}

void			update_freelist(t_chunk *prev_free, t_chunk *current,
		t_chunk *next_free)
{
	if (prev_free)
		prev_free->next_chunk = (current ? current : next_free);
	if (current)
	{
		current->prev_chunk = prev_free;
		current->next_chunk = next_free;
	}
	if (next_free)
		next_free->prev_chunk = (current ? current : prev_free);
}

void			*ft_change_header_to_free(void *ptr, void **begin_free)
{
	t_heapheader	*current_heap;
	t_chunk			*next;

	if (!(*begin_free))
	{
		ft_first_free_chunk(ptr, (((t_chunk*)ptr)->mchunk_size), NULL);
		*begin_free = ptr;
		return (ptr);
	}
	else
	{
		ft_insert_list(ptr, begin_free);
		next = ptr + ft_size_wo_flags(((t_chunk*)ptr)->mchunk_size);
		current_heap = find_current_heap(ptr);
		if (next < (t_chunk*)(current_heap->current_footer))
			set_size(next->mchunk_size | P_FLAG, next);
		return (ft_defrag(ptr, current_heap));
	}
}

void		ft_remove_from_list(t_chunk *chunk)
{
	size_t	chunk_size;
	void	**begin_list;

	chunk_size = ft_size_wo_flags(chunk->mchunk_size);
	if (!(chunk->mchunk_size & F_FLAG))
		begin_list = &(g_ptr.begin_alloc);
	else
		begin_list = (chunk_size < TINY_MAX_SIZE ? &(g_ptr.tiny_free_begin) : &(g_ptr.small_free_begin));
	if (chunk->prev_chunk)
		chunk->prev_chunk->next_chunk = chunk->next_chunk;
	if (chunk->next_chunk)
		chunk->next_chunk->prev_chunk = chunk->prev_chunk;
	*begin_list = (*begin_list == chunk ? chunk->next_chunk : *begin_list);
}