#include "ft_malloc.h"
#include <stdio.h>

void		init_free_list(void *ptr, void **end, size_t size)
{
	t_freechunk t_chunk;

	t_chunk.mchunk_prevsize = 0;
	t_chunk.mchunk_size = ft_add_flags_to_size(size, 0, 0, 0);
	t_chunk.prev_freechunk = *end;
	t_chunk.next_freechunk = NULL;

	*ptr = t_chunk;
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

static void		ft_add_free_block(void *ptr, void *prev_chk)
{
	t_freechunk t_chunk;
	
	prev_chk = (t_freechunk*)prev_chk;
	t_chunk.mchunk_prevsize = (size_t)(*ptr);
	t_chunk.mchunk_size = ft_chunk_size(ptr);
	t_chunk.prev_freechunk = prev_chk;
	t_chunk.next_freechunk = prev_chk->next_freechunk;

	*(t_freechunk*)ptr = t_chunk;

}

void			ft_change_header_to_free(void *ptr, void **begin_free, void **end_free)
{
	void *current_free;

	current_free = *begin_free;
	if (!(*begin_free))
	{
		init_free_list(ptr, end_free, ft_chunk_size(ptr));
		*begin_free = ptr;
		return;
	}
	current_free = (t_freechunk*)current_free;
	while (current_free && current_free < ptr)
		current_free = current_free->next_freechunk
	if (!(current_free))
	{
		ft_add_free_block(ptr, *end_free);
		*end = ptr;
		ptr->prev_freechunk->next_freechunk = ptr;
	}
	else
	{
		ft_add_free_block(ptr, (void*)(current_free->prev_freechunk));
		current_free->prev_freechunk = ptr;
		ptr->prev_freechunk->next_freechunk = ptr;
	}
}

