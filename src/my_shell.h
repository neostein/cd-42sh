/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_shell.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llachgar <llachgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 05:31:10 by hastid            #+#    #+#             */
/*   Updated: 2019/11/26 16:55:19 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MY_SHELL_H
# define MY_SHELL_H

# include "../libft/libft.h"
# include "../line_editing/line_editing.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <dirent.h>

typedef struct	s_tok
{
	int				id;
	char			*value;
	struct s_tok	*next;
}				t_tok;

typedef struct	s_line
{
	int		rd;
	char	**args;
}				t_line;

typedef struct	s_fd
{
	int			fir;
	int			sec;
	struct s_fd	*next;
}				t_fd;

typedef struct	s_cmdl
{
	int		rd;
	t_fd	*lrd;
	char	*excu;
	char	**args;
}				t_cmdl;

typedef struct	s_pipe
{
	t_cmdl			*cmdl;
	struct s_pipe	*next;
}				t_pipe;

typedef struct	s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}				t_env;

typedef struct	s_file
{
	int	in;
	int	out;
	int	err;
}				t_file;

int				split_pipe(char *tmp, t_env **env);
int				split_lines(char *line, t_env **env);
char			*sub_line(char **tmp, char *line, char c);
int				analy_toks(t_tok *toks);
int				check_error(t_tok *toks);
t_tok			*split_tokens(char *line);
t_cmdl			*save_to_excute(t_tok *toks, t_env *env);
int				cmd_line(char *line, t_env **env);

int				check_space(char c);
int				check_spechar(char c);
int				check_pipe(char *str);
int				check_token(char *token);
int				check_number(char *token, int check);

void			free_tab(char **tab);
void			free_pipes(t_pipe *pip);
void			free_tokens(t_tok *lst);
void			free_environ(t_env *lst);
void			free_cmdline(t_cmdl *cmdl);
int				save_tokens(t_tok **tok, char *token, int id);

int				add_args(t_cmdl *cmdl, t_tok *toks, t_env *env);
int				add_redirections(t_cmdl *cmdl, t_tok *toks);

int				execute_cmdl(t_cmdl *cmdl, char **env);

t_cmdl			*init_cmdl(void);
t_fd			*init_redirect(void);

int				check_built(char *str);
int				built_cmd(t_cmdl *cmdl, t_env **env);
int				built_echo(char **args);
int				execute(t_cmdl *cmdl, t_env **env);

void			ft_putenv(t_env *env);
int				add_elem(t_env **env, char *name, char *value);
int				del_elem(t_env **env, char *name);
t_env			*creat_env(char **env);
char			**list_to_tab(t_env *env);

int				execute_built(t_cmdl *cmdl, t_env **env);
int				built_cd(char **args, t_env **env);
char			*ft_getenv(t_env *env, char *name);

int				isdir(char *path);

int				ft_perror(char *s, char *str);
char			*parse_line(char *tmp, t_env *env);

#endif
