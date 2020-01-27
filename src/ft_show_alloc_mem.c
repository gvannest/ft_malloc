/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_show_alloc_mem.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvannest <gvannest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 17:16:47 by gvannest          #+#    #+#             */
/*   Updated: 2020/01/27 13:54:37 by cpaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void			print_info_heap(void *ptr_heap, size_t heap_size)
{
	ft_printf("begin heap : %p\n", g_ptr.begin_heap);
	ft_printf("begin current heap : %p\n", ptr_heap);
	ft_printf("footer address in header heap : %p\n",
	((t_heapheader*)ptr_heap)->current_footer);
	ft_printf("Heap size = %lu\n", heap_size);
	ft_printf("footer-> next heap hdr : %p\n\n",
	((t_heapfooter*)((t_heapheader*)ptr_heap)->current_footer)->next_heap_hdr);
}

static void		print_heap(void *ptr_heap, size_t *counter)
{
	t_heapfooter	*ptr_ftr;
	t_chunk			*ptr_chunk;
	size_t			chunk_size;

	ptr_ftr = ((t_heapheader*)ptr_heap)->current_footer;
	ptr_chunk = ptr_heap + HDR_HEAP;
	while (ptr_chunk && (void*)ptr_chunk < (void*)ptr_ftr)
	{
		chunk_size = ft_size_wo_flags(ptr_chunk->mchunk_size);
		if (!(ptr_chunk->mchunk_size & F_FLAG))
		{
			*counter += chunk_size - HDR_SIZE;
			ft_printf("%p - %p : %lu octets\n", (void*)ptr_chunk + HDR_SIZE,
					(void*)ptr_chunk + chunk_size, chunk_size - HDR_SIZE);
		}
		ptr_chunk = (void*)ptr_chunk + ft_size_wo_flags(ptr_chunk->mchunk_size);
	}
}

void			show_alloc_mem(void)
{
	t_heapheader	*ptr_heap;
	int				heap_size;
	size_t			counter;

	counter = 0;
	ptr_heap = (t_heapheader*)(g_ptr.begin_heap);
	while (ptr_heap)
	{
		heap_size = ptr_heap->current_footer + FTR_HEAP - (void*)ptr_heap;
		ft_printf("\n---------------------------------------------------\n");
		if (heap_size == getpagesize() * TINY_PAGES)
			ft_printf("TINY : %p\n", ptr_heap);
		else if (heap_size == getpagesize() * SMALL_PAGES)
			ft_printf("SMALL : %p\n", ptr_heap);
		else
			ft_printf("LARGE : %p\n", ptr_heap);
		print_heap(ptr_heap, &counter);
		ptr_heap = ((t_heapfooter*)(ptr_heap->current_footer))->next_heap_hdr;
	}
	ft_printf("---------------------------------------------------\n");
	ft_printf("Total allocated : %lu octets\n", counter);
}
