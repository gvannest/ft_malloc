/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   large_chunk.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvannest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/02 15:46:19 by gvannest          #+#    #+#             */
/*   Updated: 2020/01/02 15:53:39 by gvannest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void	ft_large_allocation(void *ptr, size_t size)
{
	t_allocchunk new_large_chunk;

	new_large_chunk.mchunk_prevsize = 0;
	new_large_chunk.mchunk_size = ft_add_flags_to_size(size, 0, 1, 0);
	*ptr = new_large_chunk;
}
