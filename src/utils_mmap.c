
#include "ft_malloc.h"

void*			call_mmap_tiny(void)
{
	return (mmap(0, getpagesize() * TINY_PAGES, PROT_READ | PROT_WRITE,
			MAP_ANONYMOUS | MAP_PRIVATE, -1, 0));
}

void*			call_mmap_small(void)
{
	return (mmap(0, getpagesize() * SMALL_PAGES, PROT_READ | PROT_WRITE,
			MAP_ANONYMOUS | MAP_PRIVATE, -1, 0));
}
