/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 01:11:57 by hastid            #+#    #+#             */
/*   Updated: 2019/11/16 02:20:27 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_21sh.h"
#include <stdio.h>

int		check_spechar(char c)
{
	if (c == '<' || c == '>' || c == '&')
		return (1);
	return (0);
}

char	*del_quotes(char *str)
{
	int		i;
	char	b;
	char	buf[1337];

	i = 0;
	if (!str)
		return (0);
	while (*str)
	{
		if (*str == 34 || *str == 39)
		{
			b = *str++;
			while (*str && *str != b)
				buf[i++] = *str++;
			str++;
		}
		buf[i++] = *str++;
	}
	buf[i] = '\0';
	return (ft_strdup(buf));
}

t_tok	*split_token(char *line)
{
	int		i;
	int		b;
	int		be;
	int		check;
	char	*tmp;
	t_tok	*lst;

	i = 0;
	lst = 0;
	check = 0;
	while (line[i])
	{
		while (line[i] && line[i] == ' ')
			i++;
		b = i;
		be = 0;
		while (line[i] && line[i] != ' ')
		{
			if (line[i] == 34 || line[i] == 39)
			{
				be = i++;
				while (line[i] && line[i] != line[be])
					i++;
			}
			if (check_spechar(line[i]) && check)
			{
				while (line[i] && check_spechar(line[i]))
					i++;
				be = 1337;
				check = 0;
				break ;
			}
			else if (check_spechar(line[i]) && !check)
			{
				be = 1337;
				check = 1;
				break ;
			}
			i++;
		}
		if (i - b > 0)
		{
			if (!(tmp = del_quotes(ft_strsub(line, b, i - b))))
				return (0);
			add_to_list(&lst, tmp, be);
			ft_memdel((void **)&tmp);
		}
	}
	/*
	t_tok 	*temp;
	temp = lst;	
	while (temp)
	{
		printf("%d -- %s\n",temp->val, temp->token);
		temp = temp->next;
	}
	*/
	return (lst);
}
