/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_cmdledit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llachgar <llachgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 09:01:03 by hastid            #+#    #+#             */
/*   Updated: 2019/11/27 16:42:18 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

int		check_valarg(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (1);
	return (0);
}

char	*edit_tilda(char *str, t_env *env)
{
	int		i;
	char	*tp;
	char	*ret;

	str++;
	ret = 0;
	if (check_valarg(*str))
	{
		i = 0;
		while (str[i] && check_valarg(str[i]))
			i++;
		ret = ft_strsub(str, 0, i);
		tp = ft_strjoin("/Users/", ret);
		ft_memdel((void **)&ret);
		ret = ft_strjoin(tp, str + i);
	}
	else if ((tp = ft_getenv(env, "HOME")))
		ret = ft_strjoin(tp, str);
	if (!ret)
		ft_perror(0, "HOME: not exists", 1);
	return (ret);
}

char	*edit_dollar(char *str, t_env *env)
{
	int		i;
	char	*tp;
	char	*tmp;
	char	*name;

	i = 0;
	str++;
	name = 0;
	while (str[i] && check_valarg(str[i]))
		i++;
	tp = ft_strsub(str, 0, i);
	tmp = ft_strsub(str + i, 0, ft_strlen(str + i));
	if (!(name = ft_getenv(env, tp)))
	{
		ft_perror(tp, ": not exists", 1);
		return (0);
	}
	if (name && tmp)
		name = ft_strjoin(name, tmp);
	else if (name)
		name = ft_strdup(name);
	ft_memdel((void **)&tp);
	ft_memdel((void **)&tmp);
	return (name);
}

char	*join_line(char *tmp, int i, t_env *env, int check)
{
	char	*tp1;
	char	*tp2;

	tp1 = ft_strsub(tmp, 0, i);
	if (tp1)
	{
		if (!check)
			tp2 = edit_tilda(tmp + i, env);
		else
			tp2 = edit_dollar(tmp + i, env);
		if (tp2)
		{
			ft_memdel((void **)&tmp);
			tmp = ft_strjoin(tp1, tp2);
			ft_memdel((void **)&tp2);
		}
		ft_memdel((void **)&tp1);
	}
	return (tmp);
}

char	*parse_line(char *tmp, t_env *env)
{
	int		i;
	int		be;

	i = 0;
	while (tmp && tmp[i])
	{
		if (tmp[i] == '~')
			if (!(tmp = join_line(tmp, i, env, 0)))
				return (0);
		if (tmp[i] == '$' && check_valarg(tmp[i + 1]))
			if (!(tmp = join_line(tmp, i, env, 1)))
				return (0);
		if (tmp[i] == 34 || tmp[i] == 39)
		{
			be = i++;
			while (tmp[i] && tmp[i] != tmp[be])
				i++;
		}
		else
			i++;
	}
	return (tmp);
}
