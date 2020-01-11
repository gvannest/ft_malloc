/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size_flags.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvannest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/02 13:28:54 by gvannest          #+#    #+#             */
/*   Updated: 2020/01/11 17:31:15 by gvannest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

size_t		ft_add_flags_to_size(size_t size_init, char a, char m, char p)
{
	return (size_init | (a * F_FLAG) | (m * M_FLAG) | (p * P_FLAG));
}

size_t		ft_size_wo_flags(size_t size)
{
	return (size & 0xFFFFFFFFFFFFFFF8);
}

size_t		ft_flags(size_t size)
{
	return (size & F_FLAG & M_FLAG & P_FLAG);
}
