/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvannest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/02 16:06:36 by gvannest          #+#    #+#             */
/*   Updated: 2020/01/11 14:11:54 by gvannest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"


static	void	ft_free_tinysmall(void *ptr, size_t size_wo_flags)
{
	if (size_wo_flags < TINY_MAX_SIZE)
		ft_change_header_to_free(ptr, &(g_ptr.tiny_free_begin));
	else if (size_wo_flags < SMALL_MAX_SIZE)
		ft_change_header_to_free(ptr, &(g_ptr.small_free_begin));
}

static	int		ft_free_large(void *ptr, size_t size_wo_flags)
{
	return munmap(ptr, size_wo_flags);
}

void			ft_free(void *ptr)
{
	// ATTENTION que faire si le pointeur n'existe pass? Que fairet le vrai malloc? a tester
	// => VERIFIER S IL APPARTIENT A L'UNE DE NOS PAGES
	size_t	chunk_size;
	size_t	size_wo_flags;

	ptr = ptr - HDR_SIZE_ALLOC;
	chunk_size = ((t_allocchunk*)ptr)->mchunk_size;
	size_wo_flags = ft_size_wo_flags(chunk_size);
	if (!size_wo_flags) //a voir ce qu'on fait peut etre virer le header
		return;
	if (chunk_size & M_FLAG)
	{
		if (ft_free_large(ptr, size_wo_flags) == -1)
			ft_printf("Error while calling munmap on large chunk\n");
	}
	else
		ft_free_tinysmall(ptr, size_wo_flags);
}
