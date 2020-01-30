/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_mmap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvannest <gvannest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 16:07:20 by gvannest          #+#    #+#             */
/*   Updated: 2020/01/30 12:06:16 by gvannest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void			*call_mmap(size_t call_size)
{
	void	*ptr;

	ptr = mmap(0, call_size, PROT_READ | PROT_WRITE,
	MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
	if (ptr == MAP_FAILED)
		exit(EXIT_FAILURE);
	return (ptr);
}

void			*prev_footer_ptr(void *ptr_heap)
{
	t_heapheader *current_heap;
	t_heapfooter *prev_footer;

	current_heap = g_ptr.begin_heap;
	prev_footer = NULL;
	while (current_heap && (void*)current_heap < ptr_heap)
	{
		prev_footer = current_heap->current_footer;
		current_heap = prev_footer->next_heap_hdr;
	}
	return (prev_footer);
}

t_heapheader	*find_current_heap(void *ptr_chunk)
{
	t_heapheader *current_heap;
	t_heapheader *prev_heap;

	current_heap = g_ptr.begin_heap;
	prev_heap = NULL;
	while (current_heap && (void*)current_heap < ptr_chunk)
	{
		prev_heap = current_heap;
		current_heap =
		((t_heapfooter*)(current_heap->current_footer))->next_heap_hdr;
	}
	return (prev_heap);
}

size_t			align_size(size_t size_user)
{
	size_t size_modif;

	size_modif = (size_user & 0xfffffffffffffff0);
	if (size_modif == size_user)
		return (size_user);
	return (size_modif + 0x10);
}

size_t			align_large_size(size_t size_user)
{
	size_t size_modif;

	size_modif = (size_user & 0xfffffffffffff000);
	if (size_modif == size_user)
		return (size_user);
	return (size_modif + 0x1000);
}
