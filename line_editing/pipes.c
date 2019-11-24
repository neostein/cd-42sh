/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llachgar <llachgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 15:36:27 by llachgar          #+#    #+#             */
/*   Updated: 2019/11/19 16:51:44 by llachgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_editing.h"

int	pipes_end(char *cmd)
{
	char	*res;
	int		i;

	res = ft_strrchr(cmd, '|');
	if (!res)
		return (1);
	i = 0;
	while (res[++i])
		if (res[i] != ' ')
			return (1);
	return (0);
}
