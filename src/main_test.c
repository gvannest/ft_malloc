/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvannest <gvannest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 17:14:41 by gvannest          #+#    #+#             */
/*   Updated: 2020/01/25 14:22:47 by gvannest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"
#include <stdio.h>
#include <time.h>
#include <math.h>
	
#include <unistd.h>

int		main(void)
{
	srand(time(NULL));
	char *tab[500];
	int i = 0;
	int	ptr_idx = 0;
	int		nbr_free = 0;
	int		nbr_malloc = 0;
	int		nbr_realloc = 0;
	int		nbr_realloc_free = 0;
	int		rand_if;

	while (i < 500)
	{
		tab[i] = NULL;
		i++;
	}
	i = 0;
	while (i < 50)
	{
		ptr_idx = rand() % 500;
		rand_if = rand() % 500;
		if (!(rand_if % 3))
		{
			nbr_free += 1;
			free(tab[ptr_idx]);
			tab[ptr_idx] = NULL;
			if (!(rand_if % 9))
			{
				nbr_realloc_free += 1;
				tab[ptr_idx] = realloc(tab[ptr_idx], rand() % 1500);
			}
		}
		else if (!(rand_if % 4))
		{
			nbr_realloc += 1;
			tab[ptr_idx] = realloc(tab[ptr_idx], rand() %1500);
		}
		else
		{
			nbr_malloc += 1;
			tab[ptr_idx] = malloc(rand() % 1500);
		}
		i += 1;
	}
	show_alloc_mem_complete();

	// print_alloc_chunk(tab[100]);
	// print_alloc_chunk(tab[200]);
	// print_alloc_chunk(tab[300]);
	
	return (0);
}