/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvannest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/20 14:37:42 by gvannest          #+#    #+#             */
/*   Updated: 2020/01/11 12:36:41 by gvannest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

t_ptr		g_ptr = {
	.tiny_free_begin = NULL,
	.small_free_begin = NULL,
	.begin_heap = NULL,
	.begin_alloc = NULL
};
