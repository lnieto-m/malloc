# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lnieto-m <lnieto-m@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/11 12:52:37 by lnieto-m          #+#    #+#              #
#    Updated: 2018/05/15 18:57:31 by lnieto-m         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME 		= libft_malloc_$(HOSTTYPE).so
CC 	 		= clang -Wall -Wextra -Werror

SRC  		= malloc.c \
			free.c \
			realloc.c \
			show_alloc_mem.c \

OBJ  		= $(SRC:%.c=objs/%.o)

SRC_DIR 	= ./srcs
INCLUDE_DIR = -I ./incs/ -I .

all: objs $(NAME)

objs:
	@mkdir objs

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -shared -o $(NAME) $(OBJ)
	@ln -s $(NAME) libft_malloc.so

objs/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDE_DIR) -o $@ -c $<

clean:
	rm -rf objs

fclean: clean
	rm -f $(NAME)
	rm -f libft_malloc.so

re: fclean all

.PHONY: all clean fclean re
