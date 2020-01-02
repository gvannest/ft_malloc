/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvannest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 17:21:19 by gvannest          #+#    #+#             */
/*   Updated: 2020/01/02 18:06:58 by gvannest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"


static void		*ft_tiny_small(size_t size, void **ptr_to_globalptr, size_t call_size)
{
	void	*ptr;

	ptr = NULL;
	if (!(*ptr_to_globalptr))
	{
		*ptr_to_globalptr = call_mmap(call_size);
		init_free_heap(*ptr_to_globalptr, call_size, NULL, 0);
		return new_allocated_chunck(*ptr_to_globalptr, size);
	}
	else if ((ptr = search_free(g_mallocptr))) //we have found a free chunk of sufficient size
		return new_allocated_chunck(ptr, size);
	else //We have not found a free chunk of sufficient size in the current free list.
	{
		ptr = call_mmap(call_size);
		// A voir demain: je ne sais pas comment lui passer l'adresse du dernier bloc free + prev_size.
		// Je pense qu'il faut conserver un pointeur vers le dernier element free. en variable globale?
		init_free_heap(ptr, call_size, 

	}
}

static void		*ft_large(size_t size, void *ptr)
{
	ptr = call_mmap(size);
	ft_large_allocation(ptr, size);
	return (ptr + sizeof(t_allocchunk));
}

void			*ft_malloc(size_t size)
{
	if (size)
	{
		if (size < TINY_MAX_SIZE)
			return (ft_tiny_small(size, &(g_mallocptr.tinychk), getpagesize() * TINY_PAGES));
		else if (size < SMALL_MAX_SIZE)
			return (ft_tiny_small(size, &(g_mallocptr.smallchk), getpagesize() * SMALL_PAGES));
		else
			return (ft_large(size, ptr));
	}
	else
		return NULL
}

