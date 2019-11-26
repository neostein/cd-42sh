/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llachgar <llachgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 17:30:16 by llachgar          #+#    #+#             */
/*   Updated: 2019/11/26 02:15:11 by llachgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_editing.h"

void	end_k(t_cmd *l)
{
	int	i;

	i = l->b_p - 1;
	home_k(l);
	while (++i < l->len)
		plus(l->cur_p, l, 0);
	l->cur = l->len;
}

void	home_k(t_cmd *l)
{
	l->cur_p->c = l->init_p->c - 1;
	l->cur_p->r = l->init_p->r - 1;
	l->cur = l->b_p;
}

void	return_k(t_cmd *l)
{
	l->res = 0;
}

void	ctl_left(t_cmd *l)
{
	int c;
	int s;

	c = 0;
	s = 0;
	while (--l->cur >= l->b_p)
	{
		if (ft_isalnum(l->chars[l->cur]))
		{
			c = 1;
			s = 0;
		}
		else
			s = 1;
		mines(l->cur_p, l);
		if (c && s)
		{
			plus(l->cur_p, l, 0);
			l->cur++;
			return ;
		}
	}
	l->cur++;
}

void	ctl_right(t_cmd *l)
{
	int c;
	int s;

	c = 0;
	s = 0;
	while (l->cur < l->len)
	{
		if (!ft_isalnum(l->chars[l->cur]))
		{
			c = 0;
			s = 1;
		}
		else
			c = 1;
		if (c && s)
			return ;
		plus(l->cur_p, l, 0);
		l->cur++;
	}
}
