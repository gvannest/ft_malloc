/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvannest <gvannest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 15:05:37 by gvannest          #+#    #+#             */
/*   Updated: 2020/01/30 12:06:03 by gvannest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void			ft_free(void *ptr)
{
	size_t			chunk_size;
	size_t			size_wo_flags;

	if (!ptr)
		return ;
	ptr = ptr - HDR_SIZE;
	if (!(control_ptr(ptr)) || (((t_chunk*)ptr)->mchunk_size & F_FLAG))
		return ;
	chunk_size = ((t_chunk*)ptr)->mchunk_size;
	size_wo_flags = ft_size_wo_flags(chunk_size);
	if (!size_wo_flags)
		return ;
	if (chunk_size & M_FLAG)
	{
		if (free_large(ptr - HDR_HEAP, size_wo_flags) == -1)
			exit(EXIT_FAILURE);
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
