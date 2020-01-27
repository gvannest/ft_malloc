/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   headers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvannest <gvannest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 16:21:16 by gvannest          #+#    #+#             */
/*   Updated: 2020/01/27 14:02:27 by cpaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void		set_prev_size(size_t prev_size, void *chunk)
{
	((t_chunk*)chunk)->mchunk_prevsize = prev_size;
}

void		set_size(size_t size, void *chunk)
{
	((t_chunk*)chunk)->mchunk_size = size;
}

void		set_prev_chunk(t_chunk *prev, void *chunk)
{
	((t_chunk*)chunk)->prev_chunk = prev;
}

void		set_next_chunk(t_chunk *next, void *chunk)
{
	((t_chunk*)chunk)->next_chunk = next;
}

t_chunk		ft_set_header_free(size_t prev_size, size_t chunk_size,
									t_chunk *prev_chunk, t_chunk *next_chunk)
{
	t_chunk		t_free;

	set_prev_size(prev_size, (void*)&t_free);
	set_size(chunk_size, (void*)&t_free);
	set_prev_chunk(prev_chunk, (void*)&t_free);
	set_next_chunk(next_chunk, (void*)&t_free);
	return (t_free);
}
