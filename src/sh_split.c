/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 05:30:25 by hastid            #+#    #+#             */
/*   Updated: 2019/11/23 19:19:45 by hastid           ###   ########.fr       */
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
			{
				ft_memdel((void **)&tmp);
				return (0);
			}
			ft_memdel((void **)&tmp);
		}
	}
	if (analy_toks(toks) || check_error(toks))
	{
		free_tokens(toks);
		return (0);
	}
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

char	*edit_line(char *tmp, t_env *env)
{
	int	i;
	int	be;
	int	in;
	char	*tp1;
	char	*tp2;
	char	*name;
	char	*temp;

	i = 0;
	in = 0;
	temp = 0;
	while (tmp && tmp[i])
	{
		if (tmp[i] == '~')
		{
			tp1 = ft_strsub(tmp, in, i - in);
			if (temp)
				temp = ft_strjoin(tp1, ft_strjoin(temp, ft_getenv(env, "HOME")));
			else
				temp = ft_strjoin(tp1, ft_getenv(env, "HOME"));
			in = ++i;
		}
		else if (tmp[i] == '$')
		{
			tp1 = ft_strsub(tmp, in, i - in);
			be = ++i;
			while (tmp [i] && ((tmp[i] >= 'A' && tmp[i] <= 'Z') || (tmp[i] >= 'a' && tmp[i] <= 'z') || tmp[i] == '_'))
			   i++;
			tp2 = ft_strsub(tmp, be, i - be);
			name = ft_getenv(env,tp2);
			if (temp && name)
				temp = ft_strjoin(temp, ft_strjoin(tp1, name));
			else if (temp)
				temp = ft_strjoin(temp, tp1);
			else if (name)
				temp = ft_strjoin(tp1, name);
			else
				temp = ft_strdup(tp1);
			ft_memdel((void **)&tp1);
			ft_memdel((void **)&tp2);
			in = i;
		}
		else
			i++;
	}
	tp1 = ft_strsub(tmp, in, i - in);
	if (temp && tp1)
		temp = ft_strjoin(temp, tp1);
	else if(tp1)
		temp = ft_strdup(tp1);
	return (temp);
}

int		split_lines(char *line, t_env **env)
{
	int		i;
	int		q;
	char	*tmp;
	char	*temp;

	while (*line)
	{
		while (*line && check_space(*line))
			line++;
		if (*line)
		{
			if (!(line = sub_line(&tmp, line, ';')))
				return (1);
			temp = edit_line(tmp, *env);
			if (check_pipe(temp))
				split_pipe(temp, env);
			else
				cmd_line(temp, env);
			ft_memdel((void **)&tmp);
		}
	}
	return (0);
}
