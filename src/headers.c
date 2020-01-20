/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   headers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvannest <gvannest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 16:21:16 by gvannest          #+#    #+#             */
/*   Updated: 2020/01/18 17:47:59 by gvannest         ###   ########.fr       */
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

void			set_next_freechunk(t_chunk *next, void *chunk)
{
	((t_chunk*)chunk)->next_freechunk = next;
}

t_chunk		ft_set_header_free(size_t prev_size, size_t chunk_size, t_chunk *prev_chunk, t_chunk *next_chunk)
{
	t_chunk		t_free;
	
	set_prev_size(prev_size, (void*)&t_free);
	set_size(chunk_size, (void*)&t_free);
	set_prev_chunk(prev_chunk, (void*)&t_free);
	set_next_freechunk(next_chunk, (void*)&t_free);

	return t_free;
}


void		ft_del_free_list(t_chunk *chunk)
{
	if (chunk->prev_chunk)
		chunk->prev_chunk->next_freechunk = chunk->next_freechunk;
	if (chunk->next_freechunk)
		chunk->next_freechunk->prev_chunk = chunk->prev_chunk;
}

