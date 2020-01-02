
#include "ft_malloc.h"

void	*search_free(void *free_chuncks_list, size_t size_user)
{
// Declaration of a new ptr in order to keep tiny/small_chck unmodified
	void*		free_list;

	free_list = free_chuncks_list;
// Checks the size of the space available in the differents headers 
// of the different chucks in the list
	while (free_list)
	{
		if (*((size_t*)(free_list + 8)) >= size_user)
			return free_list;
		else
			free_list = (void*)(free_list + 24);
	}
	return NULL;
}
