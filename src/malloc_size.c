
#include "ft_malloc.h"

size_t		malloc_size(const void *ptr)
{
	size_t chunk_size;

	chunk_size = ft_size_wo_flags(((t_chunk*)ptr)->mchunk_size - HDR_SIZE);
	if (!find_current_heap((void*)ptr - HDR_SIZE))
		return (0);
	return (chunk_size - HDR_SIZE);
}

size_t		malloc_good_size(size_t size)
{
	if (size < SMALL_MAX_SIZE)
		return (align_size(size));
	else
		return (align_large_size(size));
}
