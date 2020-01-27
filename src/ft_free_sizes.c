/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_sizes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvannest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 16:01:06 by gvannest          #+#    #+#             */
/*   Updated: 2020/01/27 15:06:09 by cpaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

static void		free_tiny(void *ptr, t_heapheader *current_heap, size_t tmp_s)
{
	size_t			max_chunk_size;

	ptr = ft_change_header_to_free(ptr, &(g_ptr.tiny_free_begin));
	max_chunk_size = (TINY_PAGES * getpagesize()) - FTR_HEAP - HDR_HEAP;
	if ((ptr == (void*)current_heap + HDR_HEAP) &&
			(current_heap != g_ptr.begin_heap))
		if (tmp_s == max_chunk_size)
			ft_return_pages(ptr, max_chunk_size, current_heap,
					&(g_ptr.tiny_free_begin));
}

static void		free_small(void *ptr, t_heapheader *current_heap, size_t tmp_s)
{
	size_t			max_chunk_size;

	ft_change_header_to_free(ptr, &(g_ptr.small_free_begin));
	max_chunk_size = (SMALL_PAGES * getpagesize()) - FTR_HEAP - HDR_HEAP;
	if ((ptr == current_heap + HDR_HEAP) &&
			(current_heap != g_ptr.begin_heap))
		if (tmp_s == max_chunk_size)
			ft_return_pages(ptr, max_chunk_size, current_heap,
					&(g_ptr.small_free_begin));
}

void			free_tinysmall(void *ptr, size_t size_wo_flags)
{
	t_heapheader	*current_heap;
	size_t			tmp_s;

	current_heap = find_current_heap(ptr);
	ft_remove_from_list(ptr);
	tmp_s = ft_size_wo_flags(((t_chunk*)ptr)->mchunk_size);
	if (size_wo_flags - HDR_SIZE < TINY_MAX_SIZE)
		free_tiny(ptr, current_heap, tmp_s);
	else if (size_wo_flags - HDR_SIZE < SMALL_MAX_SIZE)
		free_small(ptr, current_heap, tmp_s);
}

void			ft_update_prev_footer(void *ptr)
{
	t_heapfooter	*prev_footer;
	t_heapfooter	*current_footer;

	current_footer = ((t_heapheader*)ptr)->current_footer;
	prev_footer = prev_footer_ptr(ptr);
	if (prev_footer)
		prev_footer->next_heap_hdr = current_footer->next_heap_hdr;
}

int				free_large(void *ptr, size_t size_wo_flags)
{
	t_heapfooter *footer;

	footer = ((t_heapheader*)ptr)->current_footer;
	if (g_ptr.begin_heap == ptr)
		g_ptr.begin_heap = footer->next_heap_hdr;
	else
		ft_update_prev_footer(ptr);
	return (munmap(ptr, size_wo_flags + HDR_HEAP + FTR_HEAP));
}
