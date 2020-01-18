/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvannest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/02 16:06:36 by gvannest          #+#    #+#             */
/*   Updated: 2020/01/11 14:11:54 by gvannest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"


static	void	free_tinysmall(void *ptr, size_t size_wo_flags)
{
	if (size_wo_flags < TINY_MAX_SIZE)
		ft_change_header_to_free(ptr, &(g_ptr.tiny_free_begin));
	else if (size_wo_flags < SMALL_MAX_SIZE)
		ft_change_header_to_free(ptr, &(g_ptr.small_free_begin));
}

static void		ft_update_prev_footer(void *ptr)
{
	t_heapfooter	*prev_footer;
	t_heapfooter 	*current_footer;

	current_footer = ((t_heapheader*)ptr)->current_footer;
	prev_footer = prev_footer_ptr(ptr);
	if (prev_footer)
		prev_footer->next_heap_hdr = current_footer->next_heap_hdr;
}

static	int		free_large(void *ptr, size_t size_wo_flags)
{
	t_heapfooter *footer;

	footer = ((t_heapheader*)ptr)->current_footer;
	if (g_ptr.begin_heap == ptr)
		g_ptr.begin_heap = footer->next_heap_hdr;
	else
		ft_update_prev_footer(ptr);
	
	return munmap(ptr, size_wo_flags + HDR_HEAP + FTR_HEAP);
}

void			ft_free(void *ptr)
{
	// ATTENTION que faire si le pointeur n'existe pass? Que fairet le vrai malloc? a tester
	// => VERIFIER S IL APPARTIENT A L'UNE DE NOS PAGES
	size_t			chunk_size;
	size_t			size_wo_flags;
	t_heapheader	*current_heap;

	printf("\nFREE\n");
	if (!ptr)
		return;
	ptr = ptr - HDR_SIZE_ALLOC;
	current_heap = find_current_heap(ptr);
	if (!current_heap || !((ptr > (void*)current_heap) && (ptr < current_heap->current_footer)))
		return;
	chunk_size = ((t_allocchunk*)ptr)->mchunk_size;
	size_wo_flags = ft_size_wo_flags(chunk_size);
	if (!size_wo_flags) //a voir ce qu'on fait peut etre virer le header
		return;
	if (chunk_size & M_FLAG)
	{
		if (free_large(ptr - HDR_HEAP, size_wo_flags) == -1)
			ft_printf("\x1B[31mError while calling munmap on large chunk\x1B[0m\n");
	}
	else
		free_tinysmall(ptr, size_wo_flags);
}
