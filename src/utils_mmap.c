
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
	while (current_heap && (void*)current_heap < ptr_heap)
	{
		prev_footer = current_heap->current_footer;
		current_heap = prev_footer->next_heap_hdr;
	}
	return prev_footer;
}

t_heapheader	*find_current_heap(void *ptr_chunk)
{
	t_heapheader *current_heap;
	t_heapheader *prev_heap;

	current_heap = g_ptr.begin_heap;
	prev_heap = NULL;
	while (current_heap && (void*)current_heap < ptr_chunk)
	{
		prev_heap = current_heap;
		current_heap = ((t_heapfooter*)(current_heap->current_footer))->next_heap_hdr;
	}
	return prev_heap;
}

size_t		align_size(size_t size_user)
{
	size_t size_modif;

	size_modif = (size_user & 0xfffffffffffffff8);
	if (size_modif == size_user)
		return size_user;
	return (size_modif + 0x8);
}

size_t		align_large_size(size_t size_user)
{
	size_t size_modif;

	size_modif = (size_user & 0xfffffffffffff000);
	ft_printf("size en binaire : %b\n", size_user);
	ft_printf("4096 eb binaire : %b\n", 0x1000);
	ft_printf("size_modif en binaire : %b\n", size_modif);
	if (size_modif == size_user)
		return size_user;
	return (size_modif + 0x1000);
}


t_freechunk		*ft_prev_free(void *ptr, t_freechunk *begin_free)
{
	t_freechunk *prev_chk;

	prev_chk = NULL;
	while (begin_free && (void*)begin_free < ptr)
	{
		prev_chk = begin_free;
		begin_free = begin_free->next_freechunk;
	}
	return prev_chk;
}
