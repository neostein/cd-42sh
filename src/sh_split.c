/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 00:10:37 by hastid            #+#    #+#             */
/*   Updated: 2019/11/01 04:52:55 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"
/* to delete */
#include <stdio.h>

int		split_blank(char *line)
{
	int		i;
	int		b;
	int		be;
	int		rdi;
	char	*tmp;
	t_arg	*lst;

	i = 0;
	rdi = 0;
	lst = 0;
	while (line[i])
	{
		while (line[i] && line[i] == ' ')
			i++;
		b = i;
		while (line[i] && line[i] != ' ')
		{
			if (line[i] == 34 || line[i] == 39)
			{
				be = i++;
				while (line[i] && line[i] != line[be])
					i++;
			}
			if (line[i] == '>' || line[i] == '<')
				rdi = 1;
			i++;
		}
		if (i - b > 0)
		{
			tmp = ft_strsub(line, b, i - b);
			add_to_list(&lst, tmp);
			ft_memdel((void **)&tmp);
		}
	}
	if (!rdi)
		excute_args(lst);
	else
		excute_redirections(lst);
	free_data(lst);
	return (1);
}

int		split_line(char *line)
{
	int		i;
	int		b;
	int		be;
	int		pipe;
	char	*tmp;

	i = 0;
	while (line[i])
	{
		while (line[i] && line[i] == ' ')
			i++;
		b = i;
		pipe = 0;
		while (line[i] && line[i] != ';')
		{
			if (line[i] == 34 || line[i] == 39)
			{
				be = i++;
				while (line[i] && line[i] != line[be])
					i++;
			}
			if (line[i] == '|')
				pipe = 1;
			i++;
		}
		if (i - b > 0)
		{
			tmp = ft_strsub(line, b, i - b);
			if (!pipe)
				split_blank(tmp);
			else
				split_pipes(tmp);
			ft_memdel((void **)&tmp);
		}
		i++;
	}
	return (1);
}
