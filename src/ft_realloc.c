/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvannest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 14:17:08 by gvannest          #+#    #+#             */
/*   Updated: 2020/01/11 18:17:00 by gvannest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

static void		*ft_new_alloc(void *ptr, size_t size)
{
	void*		new_ptr;

	new_ptr = ft_malloc(size);
	ft_memcpy(new_ptr, ptr, size);
	ft_free(ptr);
	return new_ptr;
}

static void		*ft_move_free_header(void *ptr, void *next_chunk)
{
}

static void		ft_next_chunk_free(void *ptr, t_freechunk *next_chunk, size_t size_user, size_t size_wo_flags)
{
	size_t		size_diff;
	size_t		next_size_wo_flags;
	char		current_flags;
	size_t		new_size;

	current_flags = ft_flags((t_allocchunk*)ptr->mchunk_size);
	next_size_wo_flags = ft_size_wo_flags(next_chunk->mchunk_size);
	size_diff = size_user - (size_wo_flags - HDR_SIZE_ALLOC)
	if (next_size_wo_flags - size_diff >= 0)
	{
		if (next_size_wo_flags - size_diff < HDR_SIZE_FREE)
		{
			ft_del_free_list(next_chunk);
			new_size = size_wo_flags + next_size_wo_flags;
			set_size(new_size | current_flags, ptr);
			*(ptr + new_size) = ft_set_header_alloc(new_size, (t_allocchunk*)(ptr + new_size)->mchunk_size & ~P_FLAG);
		}
		else
			ft_move_free_header() // descendre le free header et MAJ prev->next et next_free->prev et next->prevsize et suze current
	}
	else
		return (ft_new_alloc(ptr + HDR_SIZE_ALLOC, size));
}


char	ft_is_same_heap_size(size_t size_chunk, size_t size_user)
{
	if (size_chunk < TINY_MAX_SIZE && size_user < TINY_MAX_SIZE)
		return 1;
	if (size_chunk < SMALL_MAX_SIZE && size_user < SMALL_MAX_SIZE)
		return 1;
	return (0);
}

void			*ft_realloc(void *ptr, size_t size)
{
	t_allocchunk		*next_chunk;
	size_t		size_wo_flags;
// Ajouter realloc large
	ptr = ptr - HDR_SIZE_ALLOC;
	size_wo_flags = ft_size_wo_flags((t_allocchunk*)ptr->mchunk_size);
	if (!ft_is_same_heap_size(size_wo_flags, align_size(size)))
		return ft_new_alloc(ptr + HDR_SIZE_ALLOC, size);
	if (size_wo_flags - HDR_SIZE_ALLOC  >= align_size(size))
		return (ptr + HDR_SIZE_ALLOC);
	next_chunk = ptr + size_wo_flags;
	if (next_chunk == find_current_heap(ptr)->current_footer)
		return ft_new_alloc(ptr + HDR_SIZE_ALLOC, size);
	if (!(next_chunk->mchunk_size & F_FLAG))
		return ft_new_alloc(ptr + HDR_SIZE_ALLOC, size);
	ft_next_chunk_free(ptr, (t_freechunk*)next_chunk, size, size_wo_flags);
	}
