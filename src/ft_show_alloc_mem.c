/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_show_alloc_mem.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvannest <gvannest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 17:16:47 by gvannest          #+#    #+#             */
/*   Updated: 2020/01/23 18:14:28 by gvannest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void	print_info_heap(void *ptr_heap, size_t heap_size)
{
		ft_printf("begin heap : %p\n", g_ptr.begin_heap);
		ft_printf("begin current heap : %p\n", ptr_heap);
		ft_printf("footer address in header heap : %p\n", ((t_heapheader*)ptr_heap)->current_footer);
		ft_printf("Heap size = %lu\n", heap_size);
		ft_printf("footer-> next heap hdr : %p\n", ((t_heapfooter*)((t_heapheader*)ptr_heap)->current_footer)->next_heap_hdr);
}

void	print_free_chunk(void *ptr_free)
{
		ft_printf("free chunk : %p\n", ptr_free);
		ft_printf("header free chunk / prevsize : %lu\n", (((t_chunk*)(ptr_free))->mchunk_prevsize));
		ft_printf("header chunk (free) / size with flags : %lu\n", (((t_chunk*)(ptr_free))->mchunk_size));
		ft_printf("header chunk (free) / size wo flags : %lu\n", ft_size_wo_flags(((t_chunk*)(ptr_free))->mchunk_size));
		ft_printf("header chunk (free) / prev_chunk : %p\n", (((t_chunk*)(ptr_free))->prev_chunk));
		ft_printf("header chunk (free) / next_chunk : %p\n", (((t_chunk*)(ptr_free))->next_chunk));
}

void		convert_to_hex(void *ptr)
{
	int		index;
	char	hex_value[9];

	index = 7;
	ft_bzero(hex_value, 9);
	printf(" 0x");
	while (index >= 0)
	{
		hex_value[index] = BASE[(*((unsigned char*)(ptr))) % 16];
		index--;
		hex_value[index] = BASE[( (*((unsigned char*)(ptr)) / 16) % 16) ];
		index--;
		ptr++;
	}
	hex_value[8] = '\0';
	printf("%s", hex_value);
}

void	print_alloc_chunk(void *ptr_alloc)
{
		size_t	size;

		size = 0;
		printf("begin alloc chunk : %p\n", ptr_alloc);
		printf("header alloc chunk / size : %lu\n", (((t_chunk*)(ptr_alloc))->mchunk_size));
		printf("header alloc chunk / prevsize : %lu\n", (((t_chunk*)(ptr_alloc))->mchunk_prevsize));
		printf("header chunk (alloc) / size with flags : %lu\n", (((t_chunk*)(ptr_alloc))->mchunk_size));
		printf("header chunk (alloc) / size wo flags : %lu\n", ft_size_wo_flags(((t_chunk*)(ptr_alloc))->mchunk_size));
		ft_printf("header chunk (alloc) / prev_chunk : %p\n", (((t_chunk*)(ptr_alloc))->prev_chunk));
		ft_printf("header chunk (alloc) / next_chunk : %p\n", (((t_chunk*)(ptr_alloc))->next_chunk));
		while (size < ((t_chunk*)(ptr_alloc))->mchunk_size - HDR_SIZE)
		{	
			if (!(size) || (size % 16 == 0))
				printf("%p: ", (void*)(ptr_alloc + HDR_SIZE + size));
			convert_to_hex((void*)(ptr_alloc + HDR_SIZE + size));
			size += 4;
			if (size / 16 && (size % 16 == 0))
				printf("\n");
		}
}



static void		print_heap(void *ptr_heap)
{
	t_heapfooter	*ptr_ftr;
	t_chunk	*ptr_chunk;
	size_t			chunk_size;

	ptr_ftr = ((t_heapheader*)ptr_heap)->current_footer;
	ptr_chunk = ptr_heap + HDR_HEAP;
	while (ptr_chunk && (void*)ptr_chunk != (void*)ptr_ftr)
	{
		chunk_size = ft_size_wo_flags(ptr_chunk->mchunk_size);
		if ((ptr_chunk->mchunk_size & F_FLAG))
			ft_printf("%p - %p : %lu octets -> FREE_BLOCK\n", (void*)ptr_chunk + HDR_SIZE,
					(void*)ptr_chunk + chunk_size, chunk_size - HDR_SIZE);
		else
			ft_printf("%p - %p : %lu octets -> ALLOCATED_BLOCK\n", (void*)ptr_chunk + HDR_SIZE,
					(void*)ptr_chunk + chunk_size, chunk_size - HDR_SIZE);
		ptr_chunk = (void*)ptr_chunk + ft_size_wo_flags(ptr_chunk->mchunk_size);
	}
}

void		show_alloc_mem()
{
	t_heapheader	*ptr_heap;
	int				heap_size;

	ptr_heap = (t_heapheader*)(g_ptr.begin_heap);
	while (ptr_heap)
	{
		heap_size = ptr_heap->current_footer + FTR_HEAP - (void*)ptr_heap;
		ft_printf("---------------------------------------\n");
		print_info_heap(ptr_heap, heap_size);
		if (heap_size == getpagesize() * TINY_PAGES)
			ft_printf("TINY : %p\n", ptr_heap);
		else if (heap_size == getpagesize() * SMALL_PAGES)
			ft_printf("SMALL : %p\n", ptr_heap);
		else
			ft_printf("LARGE : %p\n", ptr_heap);
		print_heap(ptr_heap);
		ptr_heap = ((t_heapfooter*)(ptr_heap->current_footer))->next_heap_hdr;
	}
}
