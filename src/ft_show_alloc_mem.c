/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_show_alloc_mem.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvannest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 17:16:47 by gvannest          #+#    #+#             */
/*   Updated: 2020/01/03 17:55:51 by gvannest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void		show_alloc_mem()
{
	void	*tiny;
	void	*small;

	tiny = g_ptr.tiny_begin;
	small = g_ptr.small_begin;
	ft_printf("TINY : %p\n", tiny);
	while (tiny)
	{
		ft_printf("%p - %p : %zu octets\n", )
	}

}
