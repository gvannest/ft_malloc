/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvannest <gvannest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 17:15:20 by gvannest          #+#    #+#             */
/*   Updated: 2020/01/23 18:57:05 by gvannest         ###   ########.fr       */
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
# define BASE	"0123456789abcdef"
# define TINY_MAX_SIZE		1025
# define TINY_PAGES			32
# define SMALL_MAX_SIZE		8193
# define SMALL_PAGES		244

# define HDR_SIZE			32

# define FTR_HEAP			8
# define HDR_HEAP			8

typedef struct		s_ptr
{
	void			*tiny_free_begin;
	void			*small_free_begin;
	void			*begin_alloc;
	void			*begin_heap;
}					t_ptr;

/*
 * Free chunk header structure. Free chunk header contains pointer to next and
 * prev free chunk header.
 */
typedef struct		s_chunk
{
	size_t				mchunk_prevsize;
	size_t				mchunk_size;
	struct s_chunk		*prev_chunk;
	struct s_chunk		*next_chunk;
}							t_chunk;

typedef struct		s_heapheader
{
	void			*current_footer;
}					t_heapheader;

typedef struct		s_heapfooter
{
	void			*next_heap_hdr;
}					t_heapfooter;

extern t_ptr	g_ptr;

void				*ft_malloc(size_t size);
void				ft_free(void *ptr);
void				*ft_realloc(void *ptr, size_t size);


void				*call_mmap(size_t call_size);

size_t				ft_add_flags_to_size(size_t size_init, char a, char m, char p);
size_t				ft_size_wo_flags(size_t size);
void				ft_first_free_chunk(void *ptr, size_t size, t_chunk *last_free);
void				*search_free(void *free_list, size_t size_user);
void				*ft_change_header_to_free(void *ptr, void **begin_free);
void				ft_large_allocation(void *ptr, size_t size);
void				*new_allocated_chunk(void* selected_chunk, size_t size_user, void **begin);
void				create_new_free_chunk(void **begin_free,t_chunk *selected_chunk, size_t size_user, t_heapheader *current_heap);
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

t_chunk				*ft_find_prev(void *ptr, void *begin_free);

void				set_prev_size(size_t prev_size, void *chunk);
void				set_size(size_t size, void *chunk);
void				set_prev_chunk(t_chunk *prev, void *chunk);
void				set_next_chunk(t_chunk *next, void *chunk);
t_chunk				ft_set_header_free(size_t prev_size, size_t chunk_size, t_chunk *prev_chunk, t_chunk *next_chunk);
void				ft_remove_from_list(t_chunk *chunk);
size_t				ft_flags(size_t size);

void				update_freelist(t_chunk *prev_free, t_chunk* current, t_chunk *next_free);

void       			*calloc(size_t nmemb, size_t size);
void       		*ft_defrag(void *chunk_freed, t_heapheader *current_heap);
void        	ft_return_pages(void *free_chunk, size_t max_chunk_size, t_heapheader *current_heap, void **begin_free);
void			ft_update_prev_footer(void *ptr);
#endif
