/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnieto-m <lnieto-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 13:10:13 by lnieto-m          #+#    #+#             */
/*   Updated: 2018/05/18 18:46:19 by lnieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

// mmap(0, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

// static size_t	area_size(size_t size)
// {
// 	size_t		real_size;
//
// 	real_size = ;
// 	return (real_size);
// }

// large mallocs
static void		*create_large_area(size_t size)
{
	t_area	*area;
	t_area	*ptr;

	if (!(area = mmap((void *)0, size + sizeof(t_area), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, 0, 0)))
		return (NULL);
	ptr = g_first_area;
	area->size= size + sizeof(t_area);
	area->type = LARGE;
	area->next = NULL;
	if (!g_first_area)
		g_first_area = area;
	else
	{
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = area;
	}
	return ((void *)area + sizeof(t_area));
}

static void		*create_small_tiny_area(size_t size, int type)
{
	t_area	*area;
	t_chunk	*chunk;
	t_area	*ptr;

	if (!(area = mmap((void *)0, 200 * (type + sizeof(t_chunk) + sizeof(t_area)), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, 0, 0)))
		return (NULL);
	ptr = g_first_area;
	area->size= 200 * (type + sizeof(t_area) + sizeof(t_chunk);
	area->type = type;
	area->chunk = (void *)area + sizeof(t_area);
	area->chunk->free = FALSE;
	area->chunk->size = size + sizeof(t_chunk);
	area->chunk->next = NULL;
	area->next = NULL;
	if (!g_first_area)
		g_first_area = area;
	else
	{
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = area;
	}
	return ((void *)area->chunk + sizeof(t_chunk));
}

static void		*find_space(size_t size, int type)
{
	t_area		*ptr;
	t_chunk		*current_chunk;
	int			found;

	found = 0;
	ptr = g_first_area;
	while (!found)
	{
		if (!ptr)
			return (create_small_tiny_area(size, type));
		current_chunk = ptr->chunk;
		while (current_chunk)
		{
			if (current_chunk->free
			&& size + sizeof(t_chunk) <= current_chunk->size)
			{
				current_chunk->free = FALSE;
				current_chunk->size = sizeof(t_chunk) + size;
				return ((void *)current_chunk + current_chunk->size);
			}
			if (!current_chunk->next
			&& (void *)current_chunk + current_chunk->size + size <= (void *)ptr + ptr->size))
			{
				current_chunk->next = (void *)current_chunk + current_chunk->size;
				current_chunk->next->free = FALSE;
				current_chunk->next->size = size + sizeof(t_chunk);
				current_chunk->next->next = NULL;
				return ((void *)current_chunk->next + current_chunk->next->size);
			}
			current_chunk = current_chunk->next;
		}
		ptr = ptr->next;
	}
}

static void 	*small_tiny(size)
{
	// chercher un emplacement libre


}

void			*malloc(size_t size)
{
	if (!size)
		return (NULL);
	if (size > LARGE)
		return (create_large_area(size));
	else
		// return (create_large_area(size));
		return (small_tiny(size));
		// return (NULL);
}
