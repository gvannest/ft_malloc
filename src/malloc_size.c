    //  The malloc_size() function returns the size of the memory block that
    //  backs the allocation pointed to by ptr.  The memory block size is always
    //  at least as large as the allocation it backs, and may be larger.

#include "ft_malloc.h"

size_t      malloc_size(const void *ptr)
 {
    if (!find_current_heap((void*)ptr - HDR_SIZE))
        return (0);
     return (ft_size_wo_flags(((t_chunk*)(ptr - HDR_SIZE))->mchunk_size - HDR_SIZE));
 }


    //  The malloc_good_size() function rounds size up to a value that the allo-
    //  cator implementation can allocate without adding any padding; it then
    //  returns that rounded-up value

size_t      malloc_good_size(size_t size)
{
    if (size < SMALL_MAX_SIZE)
        return align_size(size);
    else
        return align_large_size(size);
}