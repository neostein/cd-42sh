/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_argument.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 03:45:13 by hastid            #+#    #+#             */
/*   Updated: 2019/11/22 05:45:37 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

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

char	*check_path(char *str)
{
	int		i;
	char	*tmp;
	char	**path;

	i = 0;
	path = ft_strsplit("/usr/bin/:/bin/:/usr/sbin/:/sbin/:/usr/local/bin/:/usr/local/munki/", ':');
	while (path[i])
	{
		if (!(tmp = ft_strjoin(path[i], str)))
			return (0);
		if (!access(tmp, F_OK))
		{
			free_tab(path);
			return (tmp);
		}
		ft_memdel((void **)&tmp);
		i++;
	}
	free_tab(path);
	ft_perror(str, ": command not found: ");
	return (0);
}

int		add_args(t_cmdl *cmdl, t_tok *toks)
{
	int		i;

	while (toks && toks->id != 0)
		toks = toks->next;
	if (!toks || !(cmdl->excu = check_path(toks->value)))
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
