/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvannest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 17:21:19 by gvannest          #+#    #+#             */
/*   Updated: 2020/01/03 18:15:37 by gvannest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

static void		*ft_tiny_small(size_t size, size_t call_size, char flag)
{
	void	*ptr;
	void	**begin_free;
	void	**end_free;
	void	**begin;

	ptr = NULL;
	begin_free = flag == 1 ? &(g_ptr.tiny_free_begin) : &(g_ptr.small_free_begin);
	end_free = flag == 1 ? &(g_ptr.tiny_free_end) : &(g_ptr.small_free_end);
	begin = flag == 1 ? &(g_ptr.tiny_begin) : &(g_ptr.small_end);
	if (!(*begin))
	{
		*begin = call_mmap(call_size);
		(!g_ptr.begin_heap) ? g_ptr.begin_heap = *begin;
		*begin_free = *begin;
		init_free_list(*begin_free, end_free, call_size);
		return new_allocated_chunck(*begin, size);
	}
	else if ((ptr = search_free(*begin_free)))
		return new_allocated_chunck(ptr, size);
	else
	{
		ptr = call_mmap(call_size);
		init_free_list(ptr, end_free, call_size);
		return new_allocated_chunck(ptr, size);
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
			return (ft_tiny_small(size, getpagesize() * TINY_PAGES, 1));
		else if (size < SMALL_MAX_SIZE)
			return (ft_tiny_small(size, getpagesize() * SMALL_PAGES, 2));
		else
			return (ft_large(size, ptr));
	}
	else
		return NULL;
}

