/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llachgar <llachgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 05:30:25 by hastid            #+#    #+#             */
/*   Updated: 2019/11/28 18:42:51 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

static int	check_save(t_tok **toks, char *line)
{
	int		i;
	int		q;
	int		be;
	int		sp;
	char	*tmp;

	i = 0;
	sp = 0;
	while (line[i])
	{
		be = i;
		while (line[i])
		{
			if (line[i] == 34 || line[i] == 39)
			{
				q = i++;
				while (line[i] && line[i] != line[q])
					i++;
			}
			if (!sp && check_spechar(line[i]))
			{
				sp = 1;
				break ;
			}
			if (sp && check_spechar(line[i]))
			{
				sp = 0;
				while (check_spechar(line[i]))
					i++;
				break ;
			}
			i++;
		}
		if (i - be > 0)
		{
			if (!(tmp = ft_strsub(line, be, i - be)))
				return (0);
			if (save_tokens(toks, tmp, sp))
				return (1);
			ft_memdel((void **)&tmp);
		}
	}
	return (0);
}

static char	*sub_token(char **tmp, char *line)
{
	int	i;
	int	q;

	i = 0;
	while (line[i] && !check_space(line[i]))
	{
		if (line[i] == 34 || line[i] == 39)
		{
			q = i++;
			while (line[i] && line[i] != line[q])
				i++;
		}
		i++;
	}
	if (!(*tmp = ft_strsub(line, 0, i)))
		return (0);
	while (line[i] && check_space(line[i]))
		i++;
	return (line + i);
}

t_tok		*split_tokens(char *line)
{
	char	*tmp;
	t_tok	*toks;

	toks = 0;
	while (*line)
	{
		while (*line && check_space(*line))
			line++;
		if (*line)
		{
			line = sub_token(&tmp, line);
			if (tmp)
			{
				if (check_save(&toks, tmp))
				{
					ft_memdel((void **)&tmp);
					return (0);
				}
				ft_memdel((void **)&tmp);
			}
		}
	}
	return (toks);
}

char		*sub_line(char **tmp, char *line, char c)
{
	int	i;
	int	q;

	i = 0;
	while (line[i] && line[i] != c)
	{
		if (line[i] == 34 || line[i] == 39)
		{
			q = i++;
			while (line[i] && line[i] != line[q])
				i++;
		}
		i++;
	}
	*tmp = ft_strsub(line, 0, i);
	if (line[i])
		return (line + i + 1);
	return (line + i);
}

int			split_lines(char *line, t_env **env)
{
	int		i;
	char	*tmp;
	char	*temp;

	while (*line)
	{
		while (*line && check_space(*line))
			line++;
		if (*line)
		{
			line = sub_line(&tmp, line, ';');
			if (tmp && (temp = parse_line(tmp, *env)))
			{
				if (check_pipe(temp))
					split_pipe(temp, env);
				else if (cmd_line(temp, env) == -1)
				{
					ft_memdel((void **)&temp);
					return (-1);
				}
				ft_memdel((void **)&temp);
			}
		}
	}
	return (0);
}
