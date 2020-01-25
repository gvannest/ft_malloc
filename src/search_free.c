/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vim free_operations.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvannest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 14:34:30 by gvannest          #+#    #+#             */
/*   Updated: 2020/01/25 14:48:57 by gvannest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void		*search_free(void *free_list, size_t size_user)
{
	t_chunk		*list_copy;

	list_copy = (t_chunk*)free_list;
	while (list_copy)
	{
		if (ft_size_wo_flags(list_copy->mchunk_size) >= (size_user + HDR_SIZE))
			return (void*)list_copy;
		else
			list_copy = list_copy->next_chunk;
	}
	return NULL;
}

