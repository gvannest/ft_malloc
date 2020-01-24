/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvannest <gvannest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/20 14:37:42 by gvannest          #+#    #+#             */
/*   Updated: 2020/01/24 14:44:12 by gvannest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

t_ptr		g_ptr = {
	.tiny_free_begin = NULL,
	.small_free_begin = NULL,
	.begin_heap = NULL,
	.begin_alloc = NULL,
};

pthread_mutex_t g_mutex = PTHREAD_MUTEX_INITIALIZER;
