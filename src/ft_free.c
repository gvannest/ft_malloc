/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvannest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/02 16:06:36 by gvannest          #+#    #+#             */
/*   Updated: 2020/01/04 15:56:03 by gvannest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"


static	void	ft_free_tinysmall(void *ptr)
{
	size_t chunk_size;

	chunk_size = ft_chunk_size(ptr);
	if (ft_size_wo_flags(chunk_size) < TINY_MAX_SIZE)
		ft_change_header_to_free(ptr, &(g_ptr.tiny_free_begin), &(g_ptr.tiny_free_end));
	else if (ft_size_wo_flags(chunk_size) < SMALL_MAX_SIZE)
		ft_change_header_to_free(ptr, &(g_ptr.small_free_begin), &(g_ptr.small_free_end));
}

static	int		ft_free_large(void *ptr, size_t size_wo_flags)
{
	return munmap(ptr, size_wo_flags);
}

void			ft_free(void *ptr)
{
	// ATTENTION que faire si le pointeur n'existe pass? Que fairet le vrai malloc? a tester
	ptr = ptr - HDR_SIZE_ALLOC;
	chunk_size = ft_chunk_size(ptr);
	size_wo_flags = ft_size_wo_flags(chunk_size);
	if (!size_wo_flags) //a voir ce qu'on fait peut etre virer le header
		return;
	if (chunk_size & M_FLAG)
		if (ft_free_large(ptr, size_wo_flags) == -1)
			ft_printf("Error while calling munmap on large chunk\n");
	else
		ft_free_tinysmall(ptr);
}
