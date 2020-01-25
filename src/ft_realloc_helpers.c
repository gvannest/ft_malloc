/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc_helpers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvannest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 16:33:43 by gvannest          #+#    #+#             */
/*   Updated: 2020/01/25 16:35:18 by gvannest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

static void			*ft_move_free_header(void *ptr, size_t chunk_size, size_t size_diff)
{
	size_t		flags;
	size_t		current_free_size;
	void		*free_block;
	t_chunk		free_tmp;
	void		**begin_free;

	free_block = ptr + chunk_size;
	current_free_size = ft_size_wo_flags(((t_chunk *)free_block)->mchunk_size);
	flags = ft_flags(((t_chunk *)free_block)->mchunk_size);
	free_tmp = *((t_chunk*)free_block);
	*((t_chunk*)(free_block + size_diff)) = free_tmp;
	set_size((current_free_size - size_diff) | flags, free_block + size_diff);
	set_prev_size(((t_chunk *)free_block)->mchunk_prevsize + size_diff, free_block + size_diff);
	if (chunk_size < TINY_MAX_SIZE)
		begin_free = &(g_ptr.tiny_free_begin);
	else
		begin_free = &(g_ptr.small_free_begin);
	*begin_free = (*begin_free == free_block ? free_block + size_diff : *begin_free);
	return (free_block + size_diff);
}

static void		ft_update_current_size(void *ptr, size_t new_size)
{
	set_size(new_size | ft_flags(((t_chunk*)ptr)->mchunk_size & ~F_FLAG), ptr);
}

static void		ft_update_chunk_after_free(void *prev_ptr, size_t new_size, char prev_is_free, t_heapheader *current_heap)
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

static char		ft_is_same_heap_size(size_t size_chunk, size_t size_user)
{
	if (size_chunk < TINY_MAX_SIZE && size_user < TINY_MAX_SIZE)
		return (1);
	if ((size_chunk < SMALL_MAX_SIZE && size_user < SMALL_MAX_SIZE) && (size_chunk >= TINY_MAX_SIZE && size_user >= TINY_MAX_SIZE))
		return (2);
	return (0);
}

