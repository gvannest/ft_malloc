
#include "ft_malloc.h"
/*
 * Lors de l'allocation d'un bloc, ce chunk ne sera plus disponible et donc 
 * doit etre retire de la liste des free.
 * Pour cela, il faut modifier les header dy chunk precedent et du chunk suivant.
 * 
 * Bloc suivant le bloc allour : le ptr du bloc suivant qui pointait sur le bloc allant etre alloue
 * doit etre redirige vers le bloc precedent au bloc alloue.
 * La prev_size doit aussi etre mise a jour.
 *
 * Bloc precedent au bloc allour : le ptr next_freechunk pointant sur le bloc alloue
 * doit etre redigire vers le bloc suivant le bloc aloue.
 *
 * Cependant, le chunk alloue peut etre plus grand que la taille utilisateur requise
 * il faut donc creer un nouveau chunk et cela complique la mise a jour de la liste chainee.
 *
 * Pour ce faire:
 * - je sauvegarde les ptrs prev et next du bloc aloue.
 * - je cree le nouveau chunk  et je mets a jour les pts du bloc alloue (prev et next_freechunk
 * pointent sur le nouveau chunk)
 * - je verifie avec les pts sauvegarde s'il y avait dun bloc precedent et suivant 
 *   MAIS je mets a jour avec les nouvelles ptrs next et prev (pointant sur le new chunk)
 *
 * L'object etait d'avoir le moins de fonction possible et que leur utilisation soit la meme 
 * avec ou sans nouveau bloc.
 */

static void		create_new_next_chunck(t_freechunk *selected_chunk, size_t size_user)
{
	t_freechunk		*new_chunk;

// Creation du nouveau free chunk en fonction de la size_user et de la taille du header
	new_chunk = selected_chunk + sizeof(t_allocchunk) + size_user;
	new_chunk->mchunk_prevsize = selected_chunk->mchunk_prevsize;
	new_chunk->mchunk_size = selected_chunk->mchunk_size - (size_user + sizeof(t_allocchunk));
	new_chunk->prev_freechunk = selected_chunk->prev_freechunk;
	new_chunk->next_freechunk = selected_chunk->next_freechunk;
// Mise a jour des pointeurs du bloc alloue vers ce nouveau bloc
	selected_chunk->mchunk_prevsize = new_chunk->mchunk_size;
	selected_chunk->prev_freechunk = new_chunk;
	selected_chunk->next_freechunk = new_chunk;
}

static void		update_next_chunk(t_freechunk *selected_chunk, t_freechunk *next_free_chunk, t_freechunk *prev_free_chunk)
{
	if (prev_free_chunk == NULL)
	{
		next_free_chunk->mchunk_prevsize = 0;
		next_free_chunk->prev_freechunk = prev_free_chunk;
	}
	else
	{
		next_free_chunk->mchunk_prevsize = selected_chunk->mchunk_prevsize;
		next_free_chunk->prev_freechunk = selected_chunk->prev_freechunk;
	}
}

static void		update_previous_chunk(t_freechunk* selected_chunk, t_freechunk *prev_free_chunk)
{
	prev_free_chunk->next_freechunk = selected_chunk->next_freechunk;
}

static void		update_header_allocated_chunck(t_freechunk *selected_chunk, size_t size_user)
{
	selected_chunk->mchunk_prevsize = 0;
	selected_chunk->mchunk_size = size_user + sizeof(t_allocchunk);
}


void			*new_allocated_chunk(t_freechunk* selected_chunk, size_t size_user)
{
	t_freechunk		*next_free_chunk;
	t_freechunk		*prev_free_chunk;

	next_free_chunk = selected_chunk->next_freechunk;
	prev_free_chunk = selected_chunk->prev_freechunk;
	if (selected_chunk->mchunk_size > size_user)
		create_new_next_chunck(selected_chunk, size_user);
	if (next_free_chunk != NULL)
		update_next_chunk(next_free_chunk, selected_chunk, prev_free_chunk);
	if (prev_free_chunk != NULL)
		update_previous_chunk(selected_chunk, prev_free_chunk);
	update_header_allocated_chunck(selected_chunk, size_user);
	return (selected_chunk + sizeof(t_allocchunk));
}
