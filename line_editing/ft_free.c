/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llachgar <llachgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 05:39:04 by llachgar          #+#    #+#             */
/*   Updated: 2019/12/23 11:09:16 by llachgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_editing.h"

char	*return_cmd(t_cmd *l)
{
	char tmp[2];

	tmp[0] = -3;
	tmp[1] = 0;
	if (l->ctl_c)
		return (ft_strdup(tmp));
	return (ft_strdup(l->chars));
}

void	free_out(t_cmd *l)
{
	if (l)
	{
		ft_bzero(l->chars, BUFF_SIZE);
		if (l->cur_p)
			free(l->cur_p);
		if (l->init_p)
			free(l->init_p);
		free(l);
		keep_l(NULL, 0);
	}
	ft_putchar('\n');
}

void	go_to_the_end(t_cmd *l)
{
	l->cur = l->len;
	print_cmd(l);
}
