/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvannest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 17:21:19 by gvannest          #+#    #+#             */
/*   Updated: 2019/12/20 18:07:48 by gvannest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void	*ft_malloc(size_t size)
{

}

void*	call_mmap(size_t size)
{
	void *ptr;

	ptr = NULL;
	if (size < TINY_SIZE)
		ptr = mmap(0, getpagesize() * TINY_PAGES, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
	else if (size < SMALL_SIZE) 
		ptrk = mmap(0, getpagesize() * SMALL_PAGES, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
	return ptr;
}
