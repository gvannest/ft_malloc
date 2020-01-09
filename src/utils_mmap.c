
#include "ft_malloc.h"

void		*call_mmap(size_t call_size)
{
	return (mmap(0, call_size, PROT_READ | PROT_WRITE,
			MAP_ANONYMOUS | MAP_PRIVATE, -1, 0));
}

void		*prev_footer_ptr(void *ptr_heap)
{
	t_heapheader *current_heap;
	t_heapfooter *prev_footer;

	current_heap = g_ptr.begin_heap;
	prev_footer = NULL;
	while (current_heap && current_heap < ptr_heap)
	{
		prev_footer = current_heap->current_footer;
		current_heap = current_heap->current_footer->next_heap_hdr;
	}
	return prev_footer;
}
