/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvannest <gvannest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 17:14:41 by gvannest          #+#    #+#             */
/*   Updated: 2020/01/24 14:48:51 by gvannest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"
#include <stdio.h>
#include <time.h>
#include <math.h>
	
#include <unistd.h>

int		main(void)
{

	char *tab[200];
	int i = 0;
	int ptr_idx = 0;

	while (i < 200)
	{
		tab[i] = NULL;
		i++;
	}
	i = 0;

	while (i < 200)
	{
		tab[i] = malloc(1024);
		i++;
	}
	printf("memory read after allocations: \n");
	show_alloc_mem();
	printf("-------------------------------------\n\n\n");

	i--;

	while (i > 80)
	{
		free(tab[i]);
		i--;
	}

	printf("memory read after free: \n");
	show_alloc_mem();
	// printf("-------------------------------------\n");
	// free(tab[9]);
	// printf("memory read after freeing last block: \n");
	// show_alloc_mem();
	// printf("-------------------------------------\n");
	// free(tab[8]);
	// printf("memory read after freeing second last: \n");
	// show_alloc_mem();
	// printf("-------------------------------------\n");
	// free(tab[4]);
	// printf("memory read after freeing fifth: \n");
	// show_alloc_mem();
	// printf("-------------------------------------\n");
	// free(tab[6]);
	// printf("memory read after freeing 6th: \n");
	// show_alloc_mem();
	// printf("-------------------------------------\n");
	// free(tab[5]);
	// printf("memory read after freeing 7th: \n");
	// show_alloc_mem();
	// printf("-------------------------------------\n");

/*
	srand(time(NULL));
	char *tab[10000];
	int i = 0;
	int	ptr_idx = 0;
	int		nbr_free = 0;
	int		nbr_malloc = 0;
	int		nbr_realloc = 0;
	int		nbr_realloc_free = 0;
	int		rand_if;

	while (i < 10000)
	{
		tab[i] = NULL;
		i++;
	}
	printf("RAND_MAX is : %d\n", RAND_MAX);
	i = 0;
	while (i < 25000)
	{
		ptr_idx = rand() % 10000;
		rand_if = rand() % 10000;
		if (!(rand_if % 3))
		{
			nbr_free += 1;
			free(tab[ptr_idx]);
			tab[ptr_idx] = NULL;
			if (!(rand_if % 9))
			{
				nbr_realloc_free += 1;
				tab[ptr_idx] = realloc(tab[ptr_idx], rand() % 25000);
			}
		}
		else if (!(rand_if % 4))
		{
			nbr_realloc += 1;
			tab[ptr_idx] = realloc(tab[ptr_idx], rand() % 25000);
		}
		else
		{
			nbr_malloc += 1;
			tab[ptr_idx] = malloc(rand() % 25000);

		}
		i += 1;
	}
	
	printf("RESULTS -------------------------------\n");
	printf("Number of malloc : %d\n", nbr_malloc);
	printf("Number of free : %d\n", nbr_free);
	printf("Number of realloc wo free : %d\n", nbr_realloc);
	printf("Number of realloc with free before : %d\n", nbr_realloc_free);
	// show_alloc_mem();
	*/
	return (0);
}



/*
	srand(time(NULL));
	size_t i = 1;
	char a = 0, m = 0, p = 0;
	size_t r = 0;
	size_t r_with_flags = 0;
	size_t r_wo_flags = 0;

	while (i <= 20){
		r = rand() % 32;
		a = rand() % 2;
		m = rand() % 2;
		p = rand() % 2;
		r = r << 3;
		r_with_flags = ft_add_flags_to_size(r, a, m, p);
		printf("%zu.  r = %zu      a = %d       m = %d        p = %d\n",i, r, a, m, p);
		if (r_with_flags == r + 4 * a + 2 * m + p)
			printf("\033[0;32mOK : %zu without flags is %zu with flags\n\033[0m", r, r_with_flags);
		else
			printf("\033[0;31mFAIL : %zu without flags is NOT %zu with flags\n\033[0m", r, r_with_flags);
		i++;
	}

	printf("-------------------------------------------\n");
	i = 0;
	while (i <= 20){
		r = rand() % (int)(pow(2,8) - 1);
		a = (r & F_FLAG) >> 2;
		m = (r & M_FLAG) >> 1;
		p = r & P_FLAG;
		r_wo_flags = ft_size_wo_flags(r);
		printf("%zu.  r = %zu      a = %d       m = %d        p = %d      r_wo_flags=%zu\n",i, r, a, m, p, r_wo_flags);
		if (!(r_wo_flags % 8))
			printf("\033[0;32mOK : %zu is a multiple of 8\n\033[0m", r_wo_flags);
		else
			printf("\033[0;31mFAIL : %zu is not a multiple of 8\n\033[0m", r_wo_flags);
		if (!(char)(r_wo_flags << 5))
			printf("\033[0;32mOK : %zu three LSBs are null\n\033[0m", r_wo_flags);
		else
		{
			printf("%d\n", (char)r_wo_flags << 5);
			printf("\033[0;31mFAIL : %zu three LSBs are not null\n\033[0m", r_wo_flags);
		}


		i++;
	}
	return (0);
}
*/

