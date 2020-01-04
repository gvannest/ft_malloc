
#include "ft_malloc.h"

static void		create_new_free_chunk(void *selected_chunk, size_t chunk_size, void **end)
{
	void			*new_chunk;
	t_freechunk		free_chunk;
	size_t			free_size;

	free_size = ft_size_wo_flags(selected_chunk->mchunk_size);
	free_chunk.mchunk_prevsize = chunk_size;
	free_chunk.mchunk_size = ft_add_flags_to_size(free_size, 0, 0, 0);
	free_chunk.prev_freechunk = selected_chunk;
	free_chunk.next_freechunk = selected_chunk->next_freechunk;
	new_chunk = selected_chunk + chunk_size;
	*new_chunk = free_chunk;
	if (!(free_chunk.next_freechunk))
		*end = new_chunk;
	else
	{	
		(t_freechunk*)new_chunk->next_freechunk->mchunk_prevsize = ft_add_flags_to_size(free_size, 0, 0, 1);
		(t_freechunk*)selected_chunk->next_freechunk->prev_freechunk = new_chunk;
	}
	(t_freechunk*)selected_chunk->next_freechunk = new_chunk;
}

static void		ft_chunk_allocation(void *selected_chunk, size_t chunk_size, void **begin, void **end)
{
	t_allocchunk	alloc_chunk;
	t_freechunk		*prev;
	t_freechunk		*next;

	selected_chunk = (t_freechunk*)selected_chunk;
	prev = selected_chunk->prev_freechunk;
	next = selected_chunk->next_freechunk;
	if (selected_chunk == *begin)
		*begin = next;
	else
		prev->next_free_chunk = next;
	if (selected_chunk == *end)
		*end = prev;
	else
		next->prev_freechunk = prev;
	alloc_chunk.mchunk_prevsize = selected_chunk->mchunk_prevsize;
	alloc_chunk.mchunk_size = selected_chunk->mchunk_size;
}

void			*new_allocated_chunk(void* selected_chunk, size_t size_user, void **begin, void **end)
{
	size_t			chunk_size;

	selected_chunk = (t_freechunk*)selected_chunk;
	chunk_size = size_user + HDR_SIZE_ALLOC;
	if (ft_size_wo_flags(selected_chunk->mchunk_size) - chunk_size >= HDR_SIZE_FREE)
		create_new_free_chunk(selected_chunk, chunk_size, end);
	ft_chunk_allocation(selected_chunk, chunk_size)
	return (selected_chunk + HDR_SIZE_ALLOC);
}
