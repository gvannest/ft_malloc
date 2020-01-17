/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvannest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 17:14:41 by gvannest          #+#    #+#             */
/*   Updated: 2020/01/11 16:19:35 by gvannest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"
#include <stdio.h>
#include <time.h>
#include <math.h>

int		main(void)
{
	char *ptr1;
	char *ptr2;
	char *ptr3;
	//char *ptr4;
	//char *ptr5;

	ptr1 = 0;
	ptr2 = 0;
	ptr3 = 0;

	ptr1 = (char*)malloc(512);
	ptr1[0] = 'y';
	ptr1[1] = 'y';
	ptr1[2] = 'y';
	ptr1[3] = 'y';
	ptr1[4] = 'y';
	ptr1[511] = 'z';
	ptr2 = malloc(800);
	ptr3 = malloc(800);
	free(ptr2);
	show_alloc_mem();
	realloc(ptr1, 400);
	show_alloc_mem();


//	ptr = malloc(512);
//	ptr5 = malloc(13300);
//	ptr2 = malloc(5780);
//	ptr1 = malloc(512);
//	ptr3 = malloc(2845);
//	ptr4 = malloc(27800);
/*	printf("ptr %p\n", ptr);
	ptr[0] = 'y';
	ptr[1] = 'o';
	ptr[2] = 'l';
	ptr[3] = '0';
	printf("coucou %s\n", ptr);
	show_alloc_mem();
	free(ptr1);
	free(ptr);
	free(ptr2);
	free(ptr3);
	free(ptr4);
	free(ptr5);
	show_alloc_mem();


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
*/
	return (0);
}

