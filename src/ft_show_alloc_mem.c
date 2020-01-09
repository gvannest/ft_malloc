/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_show_alloc_mem.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvannest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 17:16:47 by gvannest          #+#    #+#             */
/*   Updated: 2020/01/09 17:20:26 by cpaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

static void		print_heap(void *ptr_current_heap)
{
	void	*ptr_ftr_heap;

	ptr_ftr_heap = (t_heapheader*)ptr_heap->current_footer;
	ptr_current_heap = ptr_current_heap + HDR_HEAP;
	while (ptr_current_heap && ptr_current_heap != ptr_ftr_heap)
	{
		if ()
			print();
		ptr_current_heap = ptr_current_heap + ft_size_wo_flags((t_allochunk*)ptr_heap->mchunk_size);
	}
}



void		show_alloc_mem()
{
	void	*ptr_heap;
	void	*ptr_ftr_heap;

	//ptr_heap = g_ptr.begin_heap;
	ft_printf("TINY : %p\n", tiny);
	while (ptr_heap && (t_footer)
	{
		//ptr_ftr_heap = (t_heapheader*)ptr_heap->current_footer;
		ptr_heap = ptr_heap + HDR_HEAP;
		


		ft_printf("%p - %p : %zu octets\n", )
		if ()
	}

}
