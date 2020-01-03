#include "ft_malloc.h"
#include <stdio.h>

void		init_free_list(void *ptr, void **end, size_t size)
{
	t_freechunk t_chunk;

	t_chunk.mchunk_prevsize = 0;
	t_chunk.mchunk_size = size;
	t_chunk.prev_freechunk = *end;
	t_chunk.next_freechunk = NULL;

	*(t_freechunk*)ptr = t_chunk;
	*end = ptr;
}

void		*search_free(void *free_list, size_t size_user)
{
	free_list = (t_freechunk*)free_list;
	while (free_list)
	{
		if (ft_size_wo_flags(free_list->mchunk_size) >= size_user)
			return (void*)free_list;
		else
			free_list = free_list->next_freechunk;
	}
	return NULL;
}

static void		ft_add_free_block(void *ptr, t_freechunk *prev_chk)
{
	t_freechunk t_chunk;
	
	t_chunk.mchunk_prevsize = (size_t)(*ptr);
	t_chunk.mchunk_size = ft_chunk_size(ptr);
	t_chunk.prev_freechunk = prev_chk;
	t_chunk.next_freechunk = prev_chk->next_freechunk;

	*(t_freechunk*)ptr = t_chunk;
}

void			ft_change_header_to_free(void *ptr, void **begin, void **end)
{
	void *begin_copy;

	begin_copy = *begin;
	if (!(*begin))
	{
		init_free_heap(ptr, end, ft_chunk_size(ptr));
		*begin = ptr;
		return;
	}
	begin_copy = (t_freechunk*)begin_copy;
	while (begin_copy < ptr && begin_copy)
		begin_copy = begin_copy->next_freechunk
	if (!(begin_copy))
	{
		begin_copy = *((t_freechunk**)(end));
		ft_add_free_block(ptr, begin_copy);
		*end = ptr;
	}
	else
		ft_add_free_block(ptr, begin_copy->prev_freechunk);
}

