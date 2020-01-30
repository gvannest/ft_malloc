#include "ft_malloc.h"


void    *ft_reallocf    (void *ptr, size_t size)
{
    void *new_ptr;

    new_ptr = NULL;
    if (!ptr)
        return ft_malloc(size);
    if (size + HDR_SIZE > ft_size_wo_flags(((t_chunk*)ptr)->mchunk_size))
    {
        ft_free(ptr);
        return ft_malloc(size);
    }
    new_ptr =  ft_realloc(ptr, size);
    if (!new_ptr)
        free(ptr);
    return new_ptr;
}

void    *reallocf    (void *ptr, size_t size)
{
	void	*new_ptr;

	pthread_mutex_lock(&(g_mutex));
	new_ptr = ft_reallocf(ptr, size);
	pthread_mutex_unlock(&(g_mutex));
	return new_ptr;

}