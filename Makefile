# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: llachgar <llachgar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/13 18:30:14 by hastid            #+#    #+#              #
#    Updated: 2019/11/28 18:07:40 by hastid           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 21sh

FLAG = -Wall -Wextra -Werror

SRC = src/main.c \
	  src/sh_list.c \
	  src/sh_free.c \
	  src/sh_pipe.c \
	  src/sh_check.c \
	  src/sh_split.c \
	  src/sh_token.c \
	  src/sh_error.c \
	  src/sh_envlist.c \
	  src/sh_cmdline.c \
	  src/sh_builtin.c \
	  src/sh_execute.c \
	  src/sh_filedis.c \
	  src/sh_buil_cd.c \
	  src/sh_argument.c \
	  src/sh_cmdledit.c \
	  src/sh_checkline.c \

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@make -C libft
	@make -C line_editing
	@gcc $(FLAG)  libft/libft.a line_editing/line_editing.a -ltermcap  $(OBJ) -o $(NAME)

%.o: %.c
	@gcc $(FLAC) -o $@ -c $<

clean:
	@make clean -C libft
	@make clean -C line_editing
	@rm -rf $(OBJ)

fclean: clean
	@make fclean -C libft
	@make fclean -C line_editing
	@rm -f $(NAME)

re: fclean all

