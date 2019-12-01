/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_argument.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 03:45:13 by hastid            #+#    #+#             */
/*   Updated: 2019/12/01 04:14:46 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

static int	args_len(t_tok *toks)
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

static char	*check_file(char *tmp)
{
	if (isdir(tmp))
		ft_perror(tmp, ": is a directory", 0);
	else if (!access(tmp, X_OK))
		return (ft_strdup(tmp));
	else
		ft_perror(tmp, ": Permission denied", 0);
	return (0);
}

static char	*check_path(char *str, char **path)
{
	int		i;
	char	*tp;
	char	*tmp;

	i = 0;
	while (path && path[i])
	{
		if (!(tp = ft_strjoin(path[i], "/")))
			return (0);
		if (!(tmp = ft_strjoin(tp, str)))
			return (0);
		ft_memdel((void **)&tp);
		if (!access(tmp, F_OK))
		{
			if ((tp = check_file(tmp)))
				ft_memdel((void **)&tmp);
			else
				return (0);
			return (tp);
		}
		ft_memdel((void **)&tp);
		ft_memdel((void **)&tmp);
		i++;
	}
	return (0);
}

char		*excutable(char *str, t_env *env)
{
	char	*tmp;
	char	**path;

	tmp = 0;
	if (str[0])
	{
		if (!ft_strchr(str, '/'))
		{
			path = ft_strsplit(ft_getenv(env, "PATH"), ':');
			if (path)
			{
				tmp = check_path(str, path);
				free_tab(path);
				if (tmp)
					return (tmp);
			}
		}
		if (check_built(str))
			return (ft_strdup(str));
		if (!access(str, F_OK))
			return (check_file(str));
	}
	if (!tmp)
		ft_perror(str, ": command not found", 1);
	return (tmp);
}

int			add_args(t_cmdl *cmdl, t_tok *toks)
{
	int		i;

	while (toks && toks->id != 0)
		toks = toks->next;
	if (toks)
	{
		if (!(cmdl->args = (char **)malloc(sizeof(char *) *
						(args_len(toks) + 1))))
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
	return (1);
}
