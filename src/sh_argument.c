/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_argument.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 03:45:13 by hastid            #+#    #+#             */
/*   Updated: 2019/11/27 14:42:37 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

int		isdir(char *path)
{
	DIR *dir;

	dir = opendir(path);
	if (dir != NULL)
	{
		closedir(dir);
		return (1);
	}
	return (0);
}

int		args_len(t_tok *toks)
{
	int	i;

	i = 0;
	while (toks)
	{
		if (toks->id == 0)
			i++;
		toks = toks->next;
	}
	return (i);
}

char	*ft_getenv(t_env *env, char *name)
{
	while (env)
	{
		if (!ft_strcmp(name, env->name))
			return (env->value);
		env = env->next;
	}
	return (0);
}

char	*check_path(char *str, char **path)
{
	int		i;
	char	*tp;
	char	*tmp;

	i = 0;
	while (path && path[i])
	{
		tp = ft_strjoin(path[i], "/");
		if (!(tmp = ft_strjoin(tp, str)))
			return (0);
		if (!access(tmp, F_OK))
		{
			ft_memdel((void **)&tp);
			return (tmp);
		}
		ft_memdel((void **)&tp);
		ft_memdel((void **)&tmp);
		i++;
	}
	return (0);
}

char	*excutable(char *str, t_env *env)
{
	char	*tmp;
	char	**path;

	if (check_built(str))
		return (ft_strdup(str));
	if (!access(str, F_OK) && !access(str, X_OK) && !isdir(str))
		return (ft_strdup(str));
	tmp = 0;
	path = ft_strsplit(ft_getenv(env, "PATH"), ':');
	if (path)
		tmp = check_path(str, path);
	free_tab(path);
	if (!tmp)
		ft_perror(str, ": command not found", 1);
	return (tmp);
}

int		add_args(t_cmdl *cmdl, t_tok *toks, t_env *env)
{
	int		i;

	while (toks && toks->id != 0)
		toks = toks->next;
	if (!toks || !(cmdl->excu = excutable(toks->value, env)))
		return (1);
	if (!(cmdl->args = (char **)malloc(sizeof(char *) * (args_len(toks) + 1))))
		return (1);
	i = 0;
	while (toks)
	{
		if (toks->id == 0)
		{
			if (!(cmdl->args[i] = ft_strdup(toks->value)))
				return (1);
			i++;
		}
		toks = toks->next;
	}
	cmdl->args[i] = 0;
	return (0);
}
