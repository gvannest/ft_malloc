/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_allocated_chunck.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvannest <gvannest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 10:37:51 by gvannest          #+#    #+#             */
/*   Updated: 2020/01/27 14:21:47 by cpaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

static void		cut_existing_free_block(t_chunk *selected_chunk,
			t_chunk *new_chunk, size_t chunk_size, size_t free_size)
{
	*new_chunk = ft_set_header_free(chunk_size,
	ft_add_flags_to_size(free_size, 1, 0, 1), selected_chunk,
	selected_chunk->next_chunk);
	update_freelist(selected_chunk->prev_chunk, selected_chunk, new_chunk);
}

static void		cut_existing_alloc_block(size_t chunk_size, size_t free_size,
										t_chunk *new_chunk, void **begin_free)
{
	t_chunk		*prev;
	t_chunk		*next;

	prev = ft_find_prev(new_chunk, *begin_free);
	next = prev ? prev->next_chunk : *begin_free;
	*new_chunk = ft_set_header_free(chunk_size,
	ft_add_flags_to_size(free_size, 1, 0, 0), prev, next);
	*begin_free = (prev ? *begin_free : new_chunk);
}

void			create_new_free_chunk(void **begin_free,
		t_chunk *selected_chunk, size_t chunk_size, t_heapheader *current_heap)
{
	t_chunk		*new_chunk;
	size_t		free_size;
	void		*next_block;

	free_size = ft_size_wo_flags(selected_chunk->mchunk_size) - chunk_size;
	new_chunk = (void*)selected_chunk + chunk_size;
	if (selected_chunk->mchunk_size & F_FLAG)
		cut_existing_free_block(selected_chunk, new_chunk, chunk_size,
		free_size);
	else
		cut_existing_alloc_block(chunk_size, free_size, new_chunk, begin_free);
	update_freelist(new_chunk->prev_chunk, new_chunk, new_chunk->next_chunk);
	set_size(selected_chunk->mchunk_size - free_size, (void*)selected_chunk);
	next_block = (void*)new_chunk + free_size;
	if (next_block < current_heap->current_footer)
		*((t_chunk*)next_block) = ft_set_header_free(free_size,
		((t_chunk*)next_block)->mchunk_size | P_FLAG,
		((t_chunk*)next_block)->prev_chunk, ((t_chunk*)next_block)->next_chunk);
}

static void		ft_chunk_allocation(t_chunk *selected_chunk, void **begin)
{
	t_chunk		*prev;
	t_chunk		*next;
	t_chunk		*prev_alloc;
	t_chunk		*next_alloc;

	prev = selected_chunk->prev_chunk;
	next = selected_chunk->next_chunk;
	prev_alloc = NULL;
	next_alloc = NULL;
	if (selected_chunk == *begin)
		*begin = next;
	else
		prev->next_chunk = next;
	if (next)
	{
		next->mchunk_size = next->mchunk_size & ~P_FLAG;
		next->prev_chunk = prev;
	}
	selected_chunk->mchunk_size = (selected_chunk->mchunk_size) & ~F_FLAG;
	g_ptr.begin_alloc = g_ptr.begin_alloc == NULL ?
	selected_chunk : g_ptr.begin_alloc;
	prev_alloc = ft_find_prev(selected_chunk, &g_ptr.begin_alloc);
	next_alloc = prev_alloc ? prev_alloc->next_chunk : g_ptr.begin_alloc;
	update_freelist(prev_alloc, selected_chunk, next_alloc);
}

void			*new_allocated_chunk(void *selected_chunk, size_t size_user,
																void **begin)
{
	size_t		chunk_size;
	t_chunk		*selected_cast;

	selected_cast = (t_chunk*)selected_chunk;
	chunk_size = size_user + HDR_SIZE;
	if (ft_size_wo_flags(selected_cast->mchunk_size) - chunk_size >= HDR_SIZE)
		create_new_free_chunk(begin, selected_cast, chunk_size,
		find_current_heap((void*)selected_chunk));
	ft_chunk_allocation(selected_cast, begin);
	return ((void*)selected_cast + HDR_SIZE);
}
