#include "ft_malloc.h"

void			ft_remove_from_list(t_chunk *chunk)
{
	size_t	chunk_size;
	void	**begin_list;

	chunk_size = ft_size_wo_flags(chunk->mchunk_size);
	if (!(chunk->mchunk_size & F_FLAG))
		begin_list = &(g_ptr.begin_alloc);
	else
		begin_list = (chunk_size < TINY_MAX_SIZE ? &(g_ptr.tiny_free_begin) :
		&(g_ptr.small_free_begin));
	if (chunk->prev_chunk)
		chunk->prev_chunk->next_chunk = chunk->next_chunk;
	if (chunk->next_chunk)
		chunk->next_chunk->prev_chunk = chunk->prev_chunk;
	*begin_list = (*begin_list == chunk ? chunk->next_chunk : *begin_list);
}

static void		ft_insert_list(void *ptr, void **begin_free)
{
	t_chunk		*prev_free;
	t_chunk		*next_free;

	prev_free = ft_find_prev(ptr, (t_chunk*)(*begin_free));
	next_free = NULL;
	if (*begin_free > ptr)
	{
		ft_add_free_block(ptr, NULL, *begin_free);
		((t_chunk*)(*begin_free))->prev_chunk = (t_chunk*)ptr;
		*begin_free = ptr;
	}
	else
	{
		next_free = prev_free->next_chunk;
		ft_add_free_block(ptr, prev_free, next_free);
		update_freelist(prev_free, ptr, next_free);
	}
}

void			update_freelist(t_chunk *prev_free, t_chunk *current,
		t_chunk *next_free)
{
	if (prev_free)
		prev_free->next_chunk = (current ? current : next_free);
	if (current)
	{
		current->prev_chunk = prev_free;
		current->next_chunk = next_free;
	}
	if (next_free)
		next_free->prev_chunk = (current ? current : prev_free);
}
