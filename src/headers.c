/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   headers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvannest <gvannest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 16:21:16 by gvannest          #+#    #+#             */
/*   Updated: 2020/01/23 17:09:50 by gvannest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void			set_prev_size(size_t prev_size, void *chunk)
{
	((t_chunk*)chunk)->mchunk_prevsize = prev_size;
}

void			set_size(size_t size, void *chunk)
{
	((t_chunk*)chunk)->mchunk_size = size;

}

void			set_prev_chunk(t_chunk *prev, void *chunk)
{
	((t_chunk*)chunk)->prev_chunk = prev;
}

void			set_next_chunk(t_chunk *next, void *chunk)
{
	((t_chunk*)chunk)->next_chunk = next;
}

t_chunk		ft_set_header_free(size_t prev_size, size_t chunk_size, t_chunk *prev_chunk, t_chunk *next_chunk)
{
	t_chunk		t_free;
	
	set_prev_size(prev_size, (void*)&t_free);
	set_size(chunk_size, (void*)&t_free);
	set_prev_chunk(prev_chunk, (void*)&t_free);
	set_next_chunk(next_chunk, (void*)&t_free);

	return t_free;
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

