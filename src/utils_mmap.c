
#include "ft_malloc.h"

void*			call_mmap(size_t call_size)
{
	return (mmap(0, call_size, PROT_READ | PROT_WRITE,
			MAP_ANONYMOUS | MAP_PRIVATE, -1, 0));
}
