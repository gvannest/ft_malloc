/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvannest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 14:54:29 by gvannest          #+#    #+#             */
/*   Updated: 2020/01/25 14:58:38 by gvannest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void		*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr_user;
	size_t	size_to_bz;
	size_t	s;

	if (!(ptr_user = ft_malloc(nmemb * size)))
		return (NULL);
	s = ft_size_wo_flags(((t_chunk*)(ptr_user - HDR_SIZE))->mchunk_size);
	size_to_bz = s - HDR_SIZE;
	ft_bzero(ptr_user, size_to_bz);
	return (ptr_user);
}

void		*calloc(size_t nmemb, size_t size)
{
	void	*ptr_user;

	pthread_mutex_lock(&g_mutex);
	ptr_user = ft_calloc(nmemb, size);
	pthread_mutex_unlock(&g_mutex);
	return (ptr_user);
}
