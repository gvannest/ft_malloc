/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvannest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 17:21:19 by gvannest          #+#    #+#             */
/*   Updated: 2020/01/02 14:43:44 by gvannest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"


static void		*ft_tiny(size_t size, void *ptr)
{
	(void)size;
	if (!g_mallocptr.tinychk)
	{
		g_mallocptr.tinychk = call_mmap_tiny();
		init_free_heap(g_mallocptr.tinychk, getpagesize() * TINY_PAGES, NULL);
	}
	return ptr;
}

static void		*ft_small(size_t size, void *ptr)
{
	(void)size;
	if (!g_mallocptr.smallchk)
	{
		g_mallocptr.smallchk = call_mmap_small();
		init_free_heap(g_mallocptr.smallchk, getpagesize() * SMALL_PAGES, NULL);
	}
	return ptr;
}

void			*ft_malloc(size_t size)
{
	void	*ptr;

	ptr = NULL;
	if (size)
	{
		if (size < TINY_MAX_SIZE)
			ptr =  ft_tiny(size, ptr);
		else if (size < SMALL_MAX_SIZE)
			ptr = ft_small(size, ptr);
//		else
//			ptr = ft_large;
	}
	return (ptr);
}

