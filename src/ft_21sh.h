/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_21sh.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 02:46:00 by hastid            #+#    #+#             */
/*   Updated: 2019/11/01 03:49:47 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_21SH_H
# define FT_21SH_H

# include <fcntl.h>
# include <unistd.h>
# include "../libft/libft.h"

typedef struct	s_arg
{
	char			*str;
	struct s_arg	*next;
}				t_arg;

typedef struct	s_pipe
{
	int				r;
	int				w;
	int				fd;
	char			**args;
	struct s_pipe	*next;
}				t_pipe;

void			free_tab(char **tab);
void			free_data(t_arg *lst);

char			*check_head(char *str);

int				split_line(char *line);
int				split_pipes(char *line);
int				split_blank(char *line);

int				excute_now(t_arg *lst);
int				excute_args(t_arg *lst);
int				excute_redirections(t_arg *lst);

int				add_to_list(t_arg **lst, char *str);

#endif
