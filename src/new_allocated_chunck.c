/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_allocated_chunck.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvannest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 10:37:51 by gvannest          #+#    #+#             */
/*   Updated: 2020/01/11 13:20:14 by gvannest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void			create_new_free_chunk(void **begin_free, t_freechunk *selected_chunk, size_t size_user, t_heapheader *current_heap)
{
	t_freechunk		*new_chunk;
	size_t			free_size;
	t_freechunk		*prev;
	t_freechunk		*next;
	void			*next_block;

	free_size = ft_size_wo_flags(selected_chunk->mchunk_size) - (size_user + HDR_SIZE_ALLOC);
	if (selected_chunk->mchunk_size & F_FLAG)
	{	
		new_chunk = (void*)selected_chunk + (HDR_SIZE_FREE - 16) + size_user;
		*new_chunk = ft_set_header_free(size_user + (HDR_SIZE_FREE - 16), ft_add_flags_to_size(free_size, 1, 0, 1), selected_chunk, selected_chunk->next_freechunk);
	}
	else
	{
		new_chunk = (void*)selected_chunk + (HDR_SIZE_ALLOC + size_user);
		prev = ft_prev_free(new_chunk, *begin_free);
		next = prev ? prev->next_freechunk : *begin_free;
		*new_chunk = ft_set_header_free(size_user + HDR_SIZE_ALLOC, ft_add_flags_to_size(free_size, 1, 0, 0), prev, next);
	}
	update_freelist(new_chunk->prev_freechunk, new_chunk, new_chunk->next_freechunk);
	set_size(selected_chunk->mchunk_size - free_size, (void*)selected_chunk);
	next_block = (void*)new_chunk + free_size;
	if (next_block != (current_heap->current_footer))
		*((t_allocchunk*)next_block) = ft_set_header_alloc(free_size, ((t_allocchunk*)next_block)->mchunk_size | P_FLAG);
}


static void		ft_chunk_allocation(t_freechunk *selected_chunk, void **begin)
{
	t_freechunk		*prev;
	t_freechunk		*next;

	prev = selected_chunk->prev_freechunk;
	next = selected_chunk->next_freechunk;
	if (selected_chunk == *begin)
		*begin = next;
	else
		prev->next_freechunk = next;
	if (next)
	{
		next->mchunk_size = next->mchunk_size & ~P_FLAG;
		next->prev_freechunk = prev;
	}	
	selected_chunk->mchunk_size = (selected_chunk->mchunk_size) & ~F_FLAG;

}

void			*new_allocated_chunk(void* selected_chunk, size_t size_user, void **begin)
{
	size_t			chunk_size;
	t_freechunk		*selected_cast;

	selected_cast = (t_freechunk*)selected_chunk;
	chunk_size = size_user + HDR_SIZE_ALLOC;
	if (ft_size_wo_flags(selected_cast->mchunk_size) - chunk_size >= HDR_SIZE_FREE)
		create_new_free_chunk(begin, selected_cast, size_user, find_current_heap((void*)selected_chunk));
	ft_chunk_allocation(selected_cast, begin);
	return (selected_chunk + HDR_SIZE_ALLOC);
}
