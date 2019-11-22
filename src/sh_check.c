/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 05:47:31 by hastid            #+#    #+#             */
/*   Updated: 2019/11/22 01:01:32 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

int		check_spechar(char c)
{
	if (c == '>' || c == '<' || c == '&')
		return (1);
	return (0);
}

int		check_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	return (0);
}

int		check_token(char *token)
{
	int	i;

	i = 0;
	while (token[i])
	{
		if (check_spechar(token[i]))
			return (1);
		i++;
	}
	return (0);
}

int		check_number(char *token)
{
	int	i;

	i = 0;
	while (token[i])
	{
		if (token[i] > '9' || token[i] < '0')
			return (1);
		i++;
	}
	return (0);
}

int		check_pipe(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '|')
			return (1);
		i++;
	}
	return (0);

}
