/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_token.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 06:13:50 by hastid            #+#    #+#             */
/*   Updated: 2019/11/27 21:24:34 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

char	*del_quotes(char *str)
{
	int		i;
	char	b;
	char	buf[65535];

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

int		edit_tokenid(char *token, int id)
{
	if (check_token(token))
		return (4);
	if (!check_number(token, 0) && id == 1)
		return (14);
	if (id == 1)
		return (0);
	if (!check_number(token, 1) && id == 13)
		return (2);
	if (!ft_strcmp("-", token) && id == 13)
		return (3);
	if (id == 13)
		return (1);
	return (id);
}

int		edit_redirct(char *rd)
{
	if (!ft_strcmp(rd, ">"))
		return (5);
	if (!ft_strcmp(rd, ">&"))
		return (6);
	if (!ft_strcmp(rd, ">>"))
		return (7);
	if (!ft_strcmp(rd, "<"))
		return (8);
	if (!ft_strcmp(rd, "<&"))
		return (9);
	if (!ft_strcmp(rd, "<<"))
		return (10);
	if (!ft_strcmp(rd, "&>"))
		return (11);
	if (!ft_strcmp(rd, "&<"))
		return (12);
	return (1);
}

int		analy_toks(t_tok *toks)
{
	char	*tmp;
	t_tok	*head;

	head = toks;
	while (toks)
	{
		if ((toks->id = edit_tokenid(toks->value, toks->id)) == 4)
			toks->next->id = 13;
		toks = toks->next;
	}
	toks = head;
	while (toks)
	{
		tmp = toks->value;
		toks->value = del_quotes(tmp);
		ft_memdel((void **)&tmp);
		if (toks->id == 4)
			toks->id = edit_redirct(toks->value);
		toks = toks->next;
	}
	return (0);
}
