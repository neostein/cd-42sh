# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: llachgar <llachgar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/16 14:53:50 by llachgar          #+#    #+#              #
#    Updated: 2019/11/26 00:37:33 by llachgar         ###   ########.fr        #
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
	  signals.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@ar rc $(NAME)  $(OBJ)

%.o: %.c
	@gcc $(FLAC)  -o $@ -c $<

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all
