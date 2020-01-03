/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvannest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 17:14:41 by gvannest          #+#    #+#             */
/*   Updated: 2020/01/03 17:35:09 by gvannest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"
#include <stdio.h>
#include <time.h>
#include <math.h>

int		main(void)
{
	char	*ptr;

	free(ptr);
//	ft_malloc(512);
//
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
		a = (r & A_FLAG) >> 2;
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

