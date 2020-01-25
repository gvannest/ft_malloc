/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvannest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 15:05:37 by gvannest          #+#    #+#             */
/*   Updated: 2020/01/25 16:16:57 by gvannest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void			ft_free(void *ptr)
{
	size_t			chunk_size;
	size_t			size_wo_flags;
	t_heapheader	*current_heap;

	if (!ptr)
		return ;
	ptr = ptr - HDR_SIZE;
	current_heap = find_current_heap(ptr);
	if (!current_heap || !((ptr > (void*)current_heap) &&
				(ptr < current_heap->current_footer)) ||
			((t_chunk*)ptr)->mchunk_size & F_FLAG)
		return ;
	chunk_size = ((t_chunk*)ptr)->mchunk_size;
	size_wo_flags = ft_size_wo_flags(chunk_size);
	if (!size_wo_flags)
		return ;
	if (chunk_size & M_FLAG)
	{
		if (free_large(ptr - HDR_HEAP, size_wo_flags) == -1)
			ft_printf("\x1B[31mError while calling munmap
					on large chunk\x1B[0m\n");
		return ;
	}
	else
		free_tinysmall(ptr, size_wo_flags);
}

void			free(void *ptr)
{
	pthread_mutex_lock(&g_mutex);
	ft_free(ptr);
	pthread_mutex_unlock(&g_mutex);
}
