/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnieto-m <lnieto-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 13:43:52 by lnieto-m          #+#    #+#             */
/*   Updated: 2018/05/18 14:56:19 by lnieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include <unistd.h>
# include <sys/mman.h>

# define TINY 128
# define SMALL 1024
# define LARGE SMALL + 1
# define TRUE 1
# define FALSE 0

typedef struct		s_chunk
{
	size_t			size;
	int				free;
	struct s_chunk	*next;
}					t_chunk;

typedef struct		s_area
{
	size_t			size;
	int				type;
	t_chunk			*chunk;
	struct s_area	*next;
}					t_area;

t_area		*g_first_area;

void		*malloc(size_t size);
void		*realloc(void *ptr, size_t size);
void		free(void *ptr);
void		show_alloc_mem();

#endif
