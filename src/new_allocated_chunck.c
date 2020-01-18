/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_allocated_chunck.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvannest <gvannest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 10:37:51 by gvannest          #+#    #+#             */
/*   Updated: 2020/01/18 12:41:51 by gvannest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void			create_new_free_chunk(void **begin_free, t_freechunk *selected_chunk, size_t chunk_size, t_heapheader *current_heap)
{
	t_freechunk		*new_chunk;
	size_t			free_size;
	t_freechunk		*prev;
	t_freechunk		*next;
	void			*next_block;


	printf("\n\nFUNCTION : create_free_chunk\n");
	free_size = ft_size_wo_flags(selected_chunk->mchunk_size) - chunk_size;
	printf("FREE_SIZE: \n");
	printf("%lu\n", free_size);
	if (selected_chunk->mchunk_size & F_FLAG)
	{	
		printf("\nFREE_CHUNK SELECTED: \n");
		print_free_chunk(selected_chunk);
		printf("chunk_size : %lu\n", chunk_size);
		new_chunk = (void*)selected_chunk + chunk_size;
		printf("FREE_CHUNK SELECTED: ft_sett_header_free: \n");
		*new_chunk = ft_set_header_free(chunk_size, ft_add_flags_to_size(free_size, 1, 0, 1), selected_chunk, selected_chunk->next_freechunk);
		printf("FREE_CHUNK SELECTED: update_free_list: \n");
		update_freelist(selected_chunk->prev_freechunk, selected_chunk, new_chunk);
	}
	else
	{
		printf("\nALLOC_CHUNK SELECTED: \n");
		print_alloc_chunk(selected_chunk);
		new_chunk = (void*)selected_chunk + chunk_size;
		prev = ft_prev_free(new_chunk, *begin_free);
		next = prev ? prev->next_freechunk : *begin_free;
		*new_chunk = ft_set_header_free(chunk_size, ft_add_flags_to_size(free_size, 1, 0, 0), prev, next);
		*begin_free = (prev ? *begin_free : new_chunk);
	}
	printf("NEW_CHUNK: update_free_list: \n");
	update_freelist(new_chunk->prev_freechunk, new_chunk, new_chunk->next_freechunk);
	set_size(selected_chunk->mchunk_size - free_size, (void*)selected_chunk);
	next_block = (void*)new_chunk + free_size;
	if (next_block != (current_heap->current_footer))
		*((t_allocchunk*)next_block) = ft_set_header_alloc(free_size, ((t_allocchunk*)next_block)->mchunk_size | P_FLAG);
	printf("\nFREE_CHUNK NEW: \n");
	print_free_chunk(new_chunk);
	printf("FUNCTION : create_free_chunk --> je sors :)\n");

}


static void		ft_chunk_allocation(t_freechunk *selected_chunk, void **begin)
{
	t_freechunk		*prev;
	t_freechunk		*next;
printf("FUNCTION : chunk_allocation\n");
	prev = selected_chunk->prev_freechunk;
	next = selected_chunk->next_freechunk;
	if (selected_chunk == *begin)
		*begin = next;
	else
		prev->next_freechunk = next;
	if (next)
	{
		next->mchunk_size = next->mchunk_size & ~P_FLAG;
		next->prev_freechunk = prev;
	}	
	selected_chunk->mchunk_size = (selected_chunk->mchunk_size) & ~F_FLAG;
printf("FUNCTION : chunk_allocation --> je sors :)\n");
}

void			*new_allocated_chunk(void* selected_chunk, size_t size_user, void **begin)
{
	size_t			chunk_size;
	t_freechunk		*selected_cast;
	selected_cast = (t_freechunk*)selected_chunk;
	
	chunk_size = size_user + HDR_SIZE_ALLOC;
	if (ft_size_wo_flags(selected_cast->mchunk_size) - chunk_size >= HDR_SIZE_FREE)
	{
		if (chunk_size >= HDR_SIZE_FREE)
			create_new_free_chunk(begin, selected_cast, chunk_size, find_current_heap((void*)selected_chunk));
		else
			create_new_free_chunk(begin, selected_cast, HDR_SIZE_FREE, find_current_heap((void*)selected_chunk));
	}
	ft_chunk_allocation(selected_cast, begin);
	printf("\nSElECTED CHUNK AFTER BEING ALLOCATED: \n");
	print_alloc_chunk(selected_cast);
	return ((void*)selected_cast + HDR_SIZE_ALLOC);
}
