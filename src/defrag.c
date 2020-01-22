
#include "ft_malloc.h"

void        ft_defrag_prev(void* chunk_freed)
{
    void            *prev_free;
    void            *next;
    t_heapheader    *current_heap;

    prev_free = NULL;
    prev_free = chunk_freed - ((t_chunk*)chunk_freed)->mchunk_prevsize;
    if (prev_free)
    {
        ((t_chunk*)prev_free)->mchunk_size += ft_size_wo_flags(((t_chunk*)chunk_freed)->mchunk_size);
        current_heap = find_current_heap(chunk_freed);
        next = chunk_freed + ft_size_wo_flags(((t_chunk*)chunk_freed)->mchunk_size);
        if (next < current_heap->current_footer)
        {
            set_prev_size(ft_size_wo_flags(((t_chunk*)prev_free)->mchunk_size), next);
            set_size(ft_size_wo_flags(((t_chunk*)next)->mchunk_size) | P_FLAG, next);
        }
    }
}