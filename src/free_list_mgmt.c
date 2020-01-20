#include "ft_malloc.h"

void		ft_first_free_chunk(void *ptr, size_t size, t_chunk *prev_chk)
{
	t_chunk chunk;

	chunk.mchunk_prevsize = 0;
	chunk.mchunk_size = ft_add_flags_to_size(size, 1, 0, 0);
	chunk.prev_chunk = prev_chk;
	if (prev_chk)
		chunk.next_freechunk = prev_chk->next_freechunk;
	else
		chunk.next_freechunk = NULL;

	*(t_chunk*)ptr = chunk;
}

void		*search_free(void *free_list, size_t size_user)
{
	t_chunk		*list_copy;

	list_copy = (t_chunk*)free_list;
	while (list_copy)
	{
		if (ft_size_wo_flags(list_copy->mchunk_size) >= (size_user + HDR_SIZE))
			return (void*)list_copy;
		else
			list_copy = list_copy->next_freechunk;
	}
	return NULL;
}

static void		ft_add_free_block(void *ptr, t_chunk *prev_chk, t_chunk *next_chk)
{
	t_chunk chunk;
	
	chunk.mchunk_prevsize = ((t_chunk*)ptr)->mchunk_prevsize;
	chunk.mchunk_size = (((t_chunk*)ptr)->mchunk_size) | F_FLAG;
	chunk.prev_chunk = prev_chk;
	chunk.next_freechunk = next_chk;

	*(t_chunk*)ptr = chunk;

}

static void		ft_insert_free_list(void *ptr, void **begin_free)
{
	t_chunk		*prev_free;
	t_chunk		*next_free;

	prev_free = ft_prev_free(ptr, (t_chunk*)(*begin_free));
	next_free = NULL;
	if (*begin_free > ptr)
	{
		ft_add_free_block(ptr, NULL, *begin_free);
		((t_chunk*)(*begin_free))->prev_chunk = (t_chunk*)ptr;
		*begin_free = ptr;
	}
	else
	{
		next_free = prev_free->next_freechunk;
		ft_add_free_block(ptr, prev_free, next_free);
		prev_free->next_freechunk = (t_chunk*)ptr;
		if (next_free)
			next_free->prev_chunk = ptr;
	}
}

void			ft_change_header_to_free(void *ptr, void **begin_free)
{
	if (!(*begin_free))
	{
		ft_first_free_chunk(ptr, (((t_chunk*)ptr)->mchunk_size), NULL);
		*begin_free = ptr;
	}
	else
		ft_insert_free_list(ptr, begin_free);
}


void	update_freelist(t_chunk *prev_free, t_chunk* current, t_chunk *next_free)
{
	if (prev_free)
		prev_free->next_freechunk = (current ? current : next_free);
	if (current)
	{
		current->prev_chunk = prev_free;
		current->next_freechunk = next_free;
	}
	if (next_free)
		next_free->prev_chunk = (current ? current : prev_free);
}
