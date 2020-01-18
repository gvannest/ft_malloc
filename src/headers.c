/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   headers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvannest <gvannest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 16:21:16 by gvannest          #+#    #+#             */
/*   Updated: 2020/01/18 12:07:06 by gvannest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void			set_prev_size(size_t prev_size, void *chunk)
{
	((t_allocchunk*)chunk)->mchunk_prevsize = prev_size;
}

void			set_size(size_t size, void *chunk)
{
	((t_allocchunk*)chunk)->mchunk_size = size;

}

void			set_prev_freechunk(t_freechunk *prev, void *chunk)
{
	((t_freechunk*)chunk)->prev_freechunk = prev;
}

void			set_next_freechunk(t_freechunk *next, void *chunk)
{
	((t_freechunk*)chunk)->next_freechunk = next;
}

t_freechunk		ft_set_header_free(size_t prev_size, size_t chunk_size, t_freechunk *prev_chunk, t_freechunk *next_chunk)
{
	t_freechunk		t_free;
	
	set_prev_size(prev_size, (void*)&t_free);
	set_size(chunk_size, (void*)&t_free);
	set_prev_freechunk(prev_chunk, (void*)&t_free);
	set_next_freechunk(next_chunk, (void*)&t_free);

	return t_free;
}

t_allocchunk	ft_set_header_alloc(size_t prev_size, size_t chunk_size)
{
	t_allocchunk		t_alloc;

	set_prev_size(prev_size, (void*)&t_alloc);
	set_size(chunk_size, (void*)&t_alloc);

	return t_alloc;
}

void		ft_del_free_list(t_freechunk *chunk)
{
	if (chunk->prev_freechunk)
		chunk->prev_freechunk->next_freechunk = chunk->next_freechunk;
	if (chunk->next_freechunk)
		chunk->next_freechunk->prev_freechunk = chunk->prev_freechunk;
}

