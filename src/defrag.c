
#include "ft_malloc.h"

void        ft_merge_chunks(t_chunk *chunk_to_merge, t_chunk *chunk_to_grow, t_heapheader *current_heap)
{
    void    *next;

    next = (void*)chunk_to_merge + ft_size_wo_flags(chunk_to_merge->mchunk_size);
    ft_remove_from_list(chunk_to_merge);
    chunk_to_grow->mchunk_size += ft_size_wo_flags(chunk_to_merge->mchunk_size);
    if (next < (void*)(current_heap->current_footer))
    {
        set_size(((t_chunk*)next)->mchunk_size | P_FLAG, next);
        set_prev_size(ft_size_wo_flags(chunk_to_grow->mchunk_size), next);
    }
}

void       ft_defrag(void *chunk_freed, t_heapheader *current_heap)
{
    t_chunk     *chunk_to_merge;
    t_chunk     *chunk_to_grow;
	void        *prev;
	void        *next;

    chunk_to_grow = NULL;
    chunk_to_merge = NULL;
    next = (void*)chunk_freed + ft_size_wo_flags(((t_chunk*)chunk_freed)->mchunk_size);
    if ((next < (void*)(current_heap->current_footer)) && (((t_chunk*)next)->mchunk_size & F_FLAG))
    {
        chunk_to_merge = next;
        chunk_to_grow = chunk_freed;
        ft_merge_chunks(chunk_to_merge, chunk_to_grow, current_heap);
    }
    prev = (void*)chunk_freed - ((t_chunk*)chunk_freed)->mchunk_prevsize;
    if ((prev > (void*)current_heap) && (((t_chunk*)prev)->mchunk_size & F_FLAG))
    {
        chunk_to_merge = chunk_freed;
        chunk_to_grow = prev;
        ft_merge_chunks(chunk_to_merge, chunk_to_grow, current_heap);
    }
// Segfault => On dirait que le pointeur begin_free se decale de 8 pour pointer sur mchunk_size...
}