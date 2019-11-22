/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 05:57:21 by hastid            #+#    #+#             */
/*   Updated: 2019/11/22 06:11:47 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

int		built_echo(char **args)
{
	int i;
	int check;

	if (args[1] == NULL)
		ft_putchar('\n');
	else
	{
		i = 1;
		check = 1;
		if (!ft_strcmp("-n", args[1]))
		{
			i = 2;
			check = 0;
		}
		while (args[i])
		{
			ft_putstr(args[i]);
			if (args[i][0] != '\0')
				ft_putstr(" ");
			i++;
		}
		if (check)
			ft_putchar('\n');
	}
	return (1);
}
