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

t_chunk			*ft_find_prev(void *ptr, void *begin)
{
	t_chunk *prev_chk;
	t_chunk *begin_free;

	begin_free = (t_chunk*)begin;
	prev_chk = (NULL);
	while (begin_free && (void*)begin_free < ptr)
	{
		prev_chk = begin_free;
		begin_free = begin_free->next_chunk;
	}
	return (prev_chk);
}
