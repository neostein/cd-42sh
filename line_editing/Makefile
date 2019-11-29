# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: llachgar <llachgar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/16 14:53:50 by llachgar          #+#    #+#              #
#    Updated: 2019/11/27 21:51:53 by llachgar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = line_editing.a

FLAG = -Wall -Wextra -Werror

SRC = history.c \
	  keys.c \
	  manage_q.c \
	  read_line.c \
	  select_manage.c \
	  tools.c \
	  pipes.c \
	  history_keys.c \
	  save.c \
	  keys2.c \
	  init.c \
	  line_editing.c \
	  signals.c \
	  ft_free.c

OBJ = $(SRC:.c=.o)


$(NAME): $(OBJ)
	@ar rc $(NAME)  $(OBJ)

all: $(NAME)

%.o: %.c
	@gcc $(FLAC)  -o $@ -c $<

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all
