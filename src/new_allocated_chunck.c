
#include "ft_malloc.h"

static void		update_previous_chunk(void *free_chunks_list, void* prev_free_chunk, void* free_chunk)
{
	if (prev_free_chunk == &free_chunks_list)
		free_chunks_list = ((t_freechunk*)free_chunk)->next_freechunk;
	else
		((t_freechunk*)prev_free_chunk)->prev_freechunk  = ((t_freechunk*)free_chunk)->prev_freechunk;
}

static void		update_next_chunk(void* prev_free_chunk, void* next_free_chunk, void* free_chunk)
{
	if (prev_free_chunk == NULL)
	{
		((t_freechunk*)next_free_chunk)->mchunk_prevsize = 0;
		((t_freechunk*)next_free_chunk)->prev_freechunk = NULL;
	}
	else
	{
		((t_freechunk*)next_free_chunk)->mchunk_prevsize = ((t_freechunk*)free_chunk)->mchunk_prevsize;
		((t_freechunk*)next_free_chunk)->prev_freechunk = ((t_freechunk*)free_chunk)->prev_freechunk;
	}
}

static void		create_new_next_chunck(void *free_heap, void* free_chunck, size_t size_user)
{
	((t_freechunk*)free_heap)->mchunk_prevsize = ((t_freechunk*)free_chunk)->mchunk_size;
	((t_freechunk*)free_heap)->mchunk_size = ((t_freechunk*)free_chunk)->mchunk_size - size_user;
	((t_freechunk*)free_heap)->prev_freechunk = free_chunk;
	((t_freechunk*)free_heap)->next_freechunk = NULL;
}

static void		update_header_allocated_chunck(void *free_chunk, size_t size_user)
{
	((t_allocchunk*)free_chunk)->mchunk_prevsize = 0;
	((t_allocchunk*)free_chunk)->mchunk_size = size_user + sizeof(t_allocchunk);
}

void		*new_allocated_chunk(void *free_chunks_list, void* free_chunk, size_t size_user)
{
	void*	next_free_chunk;
	void*	prev_free_chunk;

	prev_free_chunk = free_chunk + 16;
	next_free_chunk = free_chunk + 24;

	if (((t_freechunk*)free_chunk)->mchunk_size > size_user)
		create_new_next_chunck();
	
	update_header_allocated_chunck(free_chunk, size_user);
	
	if (next_free_chunk != NULL)
		update_next_chunk(prev_free_chunk, next_free_chunk, free_chunk);
	
	update_previous_chunk(free_chunks_list, prev_free_chunk, free_chunk);
	
	return free_chunk + 16;
}
// Creer le nouveau chunk
// modifier le header de celui alloue. (On ne s en occupe plus)
// Mettre a jouer les headers du bloc precent et suivant
