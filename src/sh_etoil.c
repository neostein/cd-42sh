/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_etoil.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 00:43:40 by hastid            #+#    #+#             */
/*   Updated: 2019/12/04 03:37:27 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

static int	match(char *s1, char *s2)
{
	if (*s1 == '\0' && *s2 == '*')
		return (match(s1, s2 + 1));
	if (*s1 != '\0' && *s2 == '*')
		return ((match(s1 + 1, s2)) || (match(s1, s2 + 1)));
	if (*s1 == *s2 && *s2 != '\0')
		return (match(s1 + 1, s2 + 1));
	if (*s1 == '\0' && *s2 == '\0')
		return (1);
	return (0);
}

static int	save_etoil(t_tok **toks, char *str, int id)
{
	DIR				*dirp;
	struct dirent	*dp;
	int				check;

	check = 0;
	dirp = opendir(".");
	if (!dirp)
		return (1);
	while ((dp = readdir(dirp)))
		if (dp->d_name[0] != '.' && match(dp->d_name, str))
		{
			check = 1;
			if (save_tokens(toks, dp->d_name, id))
				return (1);
		}
	if (!check)
		if (save_tokens(toks, str, id))
			return (1);
	closedir(dirp);
	return (0);
}

static int	check_etoil(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		if (str[i++] == '*')
			return (1);
	return (0);
}

int			edit_etoile(t_tok **toks, char *str, int id)
{
	if (check_etoil(str))
	{
		if (save_etoil(toks, str, id))
			return (1);
	}
	else if (save_tokens(toks, str, id))
		return (1);
	return (0);
}
