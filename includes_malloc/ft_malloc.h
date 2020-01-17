/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvannest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 17:15:20 by gvannest          #+#    #+#             */
/*   Updated: 2020/01/11 15:37:54 by gvannest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include <sys/mman.h>
# include <unistd.h>
# include <stdlib.h>
# include "libft.h"

# define F_FLAG 4
# define M_FLAG 2
# define P_FLAG 1

# define TINY_MAX_SIZE		1025
# define SMALL_MAX_SIZE		8193
# define TINY_PAGES			32
# define SMALL_PAGES		244

# define HDR_SIZE_ALLOC		16
# define HDR_SIZE_FREE		32

# define FTR_HEAP			8
# define HDR_HEAP			8

typedef struct		s_ptr
{
	void			*tiny_free_begin;
	void			*small_free_begin;
	void			*begin_heap;
}					t_ptr;

/*
 * Allocated chunk header structure. Allocated chunk only has the size of the
 * previous chunk and its own size
 */
typedef struct		s_allocchunk
{
	size_t			mchunk_prevsize;
	size_t			mchunk_size;
}					t_allocchunk;

/*
 * Free chunk header structure. Free chunk header contains pointer to next and
 * prev free chunk header.
 */
typedef struct		s_freechunk
{
	size_t					mchunk_prevsize;
	size_t					mchunk_size;
	struct s_freechunk		*prev_freechunk;
	struct s_freechunk		*next_freechunk;
}							t_freechunk;

typedef struct		s_heapheader
{
	void			*current_footer;
}					t_heapheader;

typedef struct		s_heapfooter
{
	void			*next_heap_hdr;
}					t_heapfooter;

extern t_ptr	g_ptr;

void				*malloc(size_t size);
void				free(void *ptr);
void				*realloc(void *ptr, size_t size);
void				*call_mmap(size_t call_size);

size_t				ft_add_flags_to_size(size_t size_init, char a, char m, char p);
size_t				ft_size_wo_flags(size_t size);
void				ft_first_free_chunk(void *ptr, size_t size, t_freechunk *last_free);
void				*search_free(void *free_list, size_t size_user);
void				ft_change_header_to_free(void *ptr, void **begin_free);
void				ft_large_allocation(void *ptr, size_t size);
void				*new_allocated_chunk(void* selected_chunk, size_t size_user, void **begin);
void				create_new_free_chunk(void **begin_free,t_freechunk *selected_chunk, size_t size_user, t_heapheader *current_heap);
size_t				ft_add_flags_to_size(size_t size_init, char a, char m, char p);
size_t				ft_size_wo_flags(size_t size);
void				*prev_footer_ptr(void *ptr_heap);
t_heapheader		*find_current_heap(void *ptr_chunk);

size_t				align_size(size_t size_user);
size_t				align_large_size(size_t size_user);

void				show_alloc_mem(void);

void				print_free_chunk(void *ptr_free);
void				print_alloc_chunk(void *ptr_alloc);
void				print_info_heap(void *ptr_heap, size_t heap_size);

t_freechunk			*ft_prev_free(void *ptr, void *begin_free);

void				set_prev_size(size_t prev_size, void *chunk);
void				set_size(size_t size, void *chunk);
void				set_prev_freechunk(t_freechunk *prev, void *chunk);
void				set_next_freechunk(t_freechunk *next, void *chunk);
t_freechunk			ft_set_header_free(size_t prev_size, size_t chunk_size, t_freechunk *prev_chunk, t_freechunk *next_chunk);
t_allocchunk		ft_set_header_alloc(size_t prev_size, size_t chunk_size);
void				ft_del_free_list(t_freechunk *chunk);
size_t				ft_flags(size_t size);

void	update_freelist(t_freechunk *prev_free, t_freechunk* current, t_freechunk *next_free);
#endif
