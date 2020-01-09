/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvannest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 17:21:19 by gvannest          #+#    #+#             */
/*   Updated: 2020/01/09 15:55:12 by cpaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

static void		ft_set_header_footer_heap(void *ptr_heap, size_t call_size)
{
	t_heapfooter	t_footer;
	t_heapfooter	*prev_footer;
	t_heapheader	t_header;

	t_footer.end_of_zone = END_ZONE_FLAG | END_HEAP_FLAG;
	t_footer.next_heap_hdr = NULL;
	(void*)(t_header.current_footer) = ptr_heap + call_size - FTR_HEAP;
	prev_footer = prev_footer_ptr(ptr_heap);
	if (prev_footer && !(prev_footer->end_of_zone & END_HEAP_FLAG))
	{
		t_footer.next_heap_hdr = prev_footer->next_heap_hdr;
		prev_footer->end_of_zone = END_ZONE_FLAG;
		prev_footer->next_heap_hdr = ptr_heap;
	}
	*(ptr_heap + call_size - FTR_HEAP) = t_footer;
	*(ptr_heap) = t_header;
}

static void		*ft_tiny_small(size_t size, size_t call_size, void **begin_free, void **end_free)
{
	void	*ptr;

	ptr = NULL;
	if (!(*begin_free))
	{
		*begin_free = call_mmap(call_size);
		init_free_list(*begin_free + HDR_HEAP, end_free, call_size - FTR_HEAP - HDR_HEAP);
		ft_set_header_footer_heap(*begin_free, call_size);
		(!g_ptr.begin_heap) ? g_ptr.begin_heap = *begin_free : 0;
		*begin_free = *begin_free + HDR_HEAP;
		return new_allocated_chunck(*begin_free, size, begin_free, end_free);
	}
	else if ((ptr = search_free(*begin_free)))
		return new_allocated_chunck(ptr, size, begin_free, end_free);
	else
	{
		ptr = call_mmap(call_size);
		init_free_list(ptr + HDR_HEAP, end_free, call_size - FTR_HEAP - HDR_HEAP);
		ft_set_header_footer_heap(ptr, call_size);
		return new_allocated_chunck(ptr + HDR_HEAP, size, begin_free, end_free);
	}
}

static void		*ft_large(size_t size, void *ptr)
{
	size_t call_size;

	call_size = ((size & 0xfffffffffffff000) | 0x1000);
	ptr = call_mmap(size);
	ft_large_allocation(ptr, size);
	ft_set_header_footer_heap(ptr, call_size);
	return (ptr + sizeof(t_allocchunk));
}

static size_t	align_size(size_t size_user)
{
	return ((size_user & 0xfffffffffffffff8) | 0x8);
}

void			*ft_malloc(size_t size)
{
	if (size)
	{
		size = align_size(size);
		if (size < TINY_MAX_SIZE)
			return (ft_tiny_small(size, getpagesize() * TINY_PAGES, &(g_ptr.tiny_free_begin), &(g_ptr.tiny_free_end)));
		else if (size < SMALL_MAX_SIZE)
			return (ft_tiny_small(size, getpagesize() * SMALL_PAGES, &(g_ptr.small_free_begin), &(g_ptr.small_free_end)));
		else
			return (ft_large(size, ptr));
	}
	else
		return NULL;
}
