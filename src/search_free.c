
#include "ft_malloc.h"

void	*search_free(void *free_list, size_t size_user)
{
	while (free_list)
	{
		if (*((size_t*)(free_list + 8)) >= size_user)
			return free_list;
		else
			free_list = (void*)(free_list + 24);
	}
	return NULL;
}
