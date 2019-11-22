/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 05:30:25 by hastid            #+#    #+#             */
/*   Updated: 2019/11/22 03:02:22 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

int		check_save(t_tok **toks, char *line)
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

char	*sub_token(char **tmp, char *line)
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

t_tok	*split_tokens(char *line)
{
	int		i;
	int		q;
	char	*tmp;
	t_tok	*toks;
	t_cmdl	*cmdl;

	toks = 0;
	while (*line)
	{
		while (*line && check_space(*line))
			line++;
		if (*line)
		{
			if (!(line = sub_token(&tmp, line)))
				return (0);
			if (check_save(&toks, tmp))
				return (0);
			ft_memdel((void **)&tmp);
		}
	}

	analy_toks(toks);
	if (check_error(toks))
		return (0);
	return (toks);
}

char	*sub_line(char **tmp, char *line, char c)
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
	if (!(*tmp = ft_strsub(line, 0, i)))
		return (0);
	if (line[i])
		return (line + i + 1);
	return (line + i);
}

int		cmd_line(char *line, char **env)
{
	t_tok	*toks;
	t_cmdl	*cmdl;

	if (!(toks = split_tokens(line)))
		return (1);
	if (!(cmdl = save_to_excute(toks)))
		return (1);
	if (execute_cmdl(cmdl, env))
		return (1);
	free_cmdline(cmdl);
	free_tokens(toks);
	return (0);
}

int		split_lines(char *line, char **env)
{
	int		i;
	int		q;
	char	*tmp;

	while (*line)
	{
		while (*line && check_space(*line))
			line++;
		if (*line)
		{
			if (!(line = sub_line(&tmp, line, ';')))
				return (1);
			if (check_pipe(tmp))
				split_pipe(tmp, env);
			else
				cmd_line(tmp, env);
			ft_memdel((void **)&tmp);
		}
	}
	return (0);
}
