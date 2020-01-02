/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvannest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 17:15:20 by gvannest          #+#    #+#             */
/*   Updated: 2020/01/02 13:51:41 by gvannest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include <sys/mman.h>
# include <unistd.h>
# include <stdlib.h>

# define A_FLAG 4
# define M_FLAG 2
# define P_FLAG 1

# define TINY_MAX_SIZE		1025
# define SMALL_MAX_SIZE		8193
# define TINY_PAGES			32
# define SMALL_PAGES		244

# define HDR_SIZE_ALLOC	16
# define HDR_SIZE_FREE	32

/*
 * Is it going to pass the norminette?
 * That is how they deal with it in the actual glibc malloc source
 * code
 */
#define chunk2mem(p)   ((void*)((char*)(p) + 2*SIZE_SZ))
#define mem2chunk(mem) ((mchunkptr)((char*)(mem) - 2*SIZE_SZ))

typedef struct		s_mallocptr
{
	void			*tinychk;
	void			*smallchk;
}					t_mallocptr;

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

extern t_mallocptr	g_mallocptr;

void				*ft_malloc(size_t size);
void				*call_mmap_tiny(void);
void				*call_mmap_small(void);

/*
 * THis function is used to init a new heap, i.e. a heap that has just
 * been allocated by mmap and therefore has no header.
 * It will set a free header to the beginning of the heap.
 */
void				init_free_heap(void *heap_ptr, size_t heap_size, t_freechunk *last_freechunk);

size_t				ft_add_flags_to_size(size_t size_init, char a, char m, char p);
size_t				ft_size_wo_flags(size_t size);

#endif
