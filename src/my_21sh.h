/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_21sh.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 01:13:14 by hastid            #+#    #+#             */
/*   Updated: 2019/11/16 05:00:38 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MY_21SH_H
# define MY_21SH_H

# include <fcntl.h>
# include <unistd.h>
# include "../libft/libft.h"

typedef struct	s_tok
{
	int				val;
	char			*token;
	struct s_tok	*next;
}				t_tok;

typedef struct	s_fd
{
	int				fdfirst;
	int				fdsecond;
	struct	s_fd	*next;
}				t_fd;

typedef struct	s_data
{
	int		rd;
	t_fd	*lst_rd;
	char	**args;
}				t_data;

t_tok			*split_token(char *str);
int				add_to_list(t_tok **lst, char *str, int to);

int		check_spechar(char c);

void			free_token(t_tok *lst);

#endif
