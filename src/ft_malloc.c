/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvannest <gvannest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 17:21:19 by gvannest          #+#    #+#             */
/*   Updated: 2020/01/18 17:35:06 by gvannest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

static void		ft_set_header_footer_heap(void *ptr_heap, size_t call_size)
{
	t_heapfooter	t_footer;
	t_heapfooter	*prev_footer;
	t_heapheader	t_header;
	t_footer.next_heap_hdr = NULL;
	t_header.current_footer = ptr_heap + call_size - FTR_HEAP;
	prev_footer = prev_footer_ptr(ptr_heap);
	if (prev_footer)
	{
		t_footer.next_heap_hdr = prev_footer->next_heap_hdr;
		prev_footer->next_heap_hdr = ptr_heap;
	}
	*((t_heapfooter*)(ptr_heap + call_size - FTR_HEAP)) = t_footer;
	*((t_heapheader*)(ptr_heap)) = t_header;
}

static void		*ft_tiny_small(size_t size, size_t call_size, void **begin_free)
{
	void	*ptr;

	ptr = NULL;
	if (!(*begin_free))
	{
		*begin_free = call_mmap(call_size);
		ft_first_free_chunk(*begin_free + HDR_HEAP, call_size - FTR_HEAP - HDR_HEAP, NULL);
		ft_set_header_footer_heap(*begin_free, call_size);
		(!g_ptr.begin_heap) ? g_ptr.begin_heap = *begin_free : 0;
		*begin_free = *begin_free + HDR_HEAP;
		return new_allocated_chunk(*begin_free, size, begin_free);
	}
	else if ((ptr = search_free(*begin_free, size)))
	{
		return new_allocated_chunk(ptr, size, begin_free);
	}
	else
	{
		ptr = call_mmap(call_size);
		ft_first_free_chunk(ptr + HDR_HEAP, call_size - FTR_HEAP - HDR_HEAP, ft_prev_free(ptr + HDR_HEAP, *begin_free));
		ft_set_header_footer_heap(ptr, call_size);
		return new_allocated_chunk(ptr + HDR_HEAP, size, begin_free);
	}
}

static void		*ft_large(size_t size)
{
	void	*ptr;
	size_t	call_size;

	ptr = NULL;
	call_size = align_large_size(size + HDR_HEAP + FTR_HEAP + HDR_SIZE);
	ptr = call_mmap(call_size);
	ft_large_allocation(ptr + HDR_HEAP, call_size);
	ft_set_header_footer_heap(ptr, call_size);
	(!g_ptr.begin_heap) ? g_ptr.begin_heap = ptr : 0;
	return (ptr + HDR_SIZE + HDR_HEAP);
}


void			*ft_malloc(size_t size)
{
	size = align_size(size);
	if (size < TINY_MAX_SIZE)
		return (ft_tiny_small(size, getpagesize() * TINY_PAGES, &(g_ptr.tiny_free_begin)));
	else if (size < SMALL_MAX_SIZE)
		return (ft_tiny_small(size, getpagesize() * SMALL_PAGES, &(g_ptr.small_free_begin)));
	else
		return (ft_large(size));
}
