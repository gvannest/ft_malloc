
#include "ft_malloc.h"

void	*new_chunck(void* free_chuck, size_t size_user)
{
	void*	next_free_chunk;
	void*	prev_free_chunk;

// Change information in next_free_chunk
	next_free_chunk = free_chunck + 24;
	if (next_free_chunck)
	{
	// Change previous_size to next free_chunck
		(size_t)((void*)next_free_chunck) = (size_t)((void*)free_chunck);
	// Change previous_free_chunck ptr in  next_free_chunck
		(size_t)((void*)next_free_chunck + 16) = (size_t)((void*)free_chunck + 16);
	}
// Change information in previous_free_chunk
	prev_free_chunk = free_chunck + 16;
	if (prev_free_chunck)
	{
		// Change next_freechuck ptr in previous free_chunck
		(size_t)((void*)prev_free_chunck + 24) = (size_t)((void*)free_chunck + 24);
	}
// Header of new allocated chuck
	(size_t)((void*)free_chunck) = 0;
	(size_t)((void*)free_chuck) = size_user + 16;
	return free_chuck + 16;
}
