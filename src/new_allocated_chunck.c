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

static void		create_new_free_chunk(t_freechunk *selected_chunk, size_t chunk_size)
{
	t_freechunk		*new_chunk;
	t_freechunk		free_chunk;
	size_t			free_size;
	char			p_flag;

	free_size = ft_size_wo_flags(selected_chunk->mchunk_size) - chunk_size;
	free_chunk.mchunk_prevsize = chunk_size;
	free_chunk.mchunk_size = ft_add_flags_to_size(free_size, 1, 0, 1);
	free_chunk.prev_freechunk = selected_chunk;
	free_chunk.next_freechunk = selected_chunk->next_freechunk;

	new_chunk = (void*)selected_chunk + chunk_size;
	*new_chunk = free_chunk;
	if (free_chunk.next_freechunk)
		{	
			new_chunk->next_freechunk->mchunk_prevsize = free_size;
			selected_chunk->next_freechunk->prev_freechunk = new_chunk;
		}
	selected_chunk->next_freechunk = new_chunk;
	p_flag = selected_chunk->mchunk_size & P_FLAG ? 1 : 0;
	selected_chunk->mchunk_size = ft_add_flags_to_size(chunk_size, 1, 0, p_flag);
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
		next->prev_freechunk = prev;
	selected_chunk->mchunk_size = (selected_chunk->mchunk_size) & ~F_FLAG;

}

void			*new_allocated_chunk(void* selected_chunk, size_t size_user, void **begin)
{
	size_t			chunk_size;
	t_freechunk		*selected_cast;

	selected_cast = (t_freechunk*)selected_chunk;
	chunk_size = size_user + HDR_SIZE_ALLOC;
	if (ft_size_wo_flags(selected_cast->mchunk_size) - chunk_size >= HDR_SIZE_FREE)
		create_new_free_chunk(selected_cast, chunk_size);
	ft_chunk_allocation(selected_cast, begin);
	return (selected_chunk + HDR_SIZE_ALLOC);
}
