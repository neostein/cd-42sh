# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hastid <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/07 19:31:36 by hastid            #+#    #+#              #
#    Updated: 2019/09/23 21:07:13 by hastid           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

IN = libft.h

all: $(NAME)

$(NAME):
	@gcc -Wall -Wextra -Werror -c *.c 
	@ar rc $(NAME) *.o

clean:
	@rm -f *.o

fclean: clean
	@rm -f $(NAME)

re: fclean all
