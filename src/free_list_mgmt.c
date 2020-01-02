#include "ft_malloc.h"
#include <stdio.h>

void		init_free_heap(void *heap_ptr, size_t heap_size, t_freechunk *last_freechunk)
{
	t_freechunk t_chunk;

	t_chunk.mchunk_prevsize = 0;
	t_chunk.mchunk_size = heap_size;
	t_chunk.prev_freechunk = last_freechunk;
	t_chunk.next_freechunk = NULL;

	*(t_freechunk*)heap_ptr = t_chunk;
}
