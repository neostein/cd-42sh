/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llachgar <llachgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 16:29:11 by llachgar          #+#    #+#             */
/*   Updated: 2019/11/24 19:59:49 by llachgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_editing.h"

void	right_key(t_cmd *l)
{
	if (l->cur >= l->len)
		return ;
	l->cur++;
	plus(l->cur_p, l, 0);
}

void	left_key(t_cmd *l)
{
	if (l->cur - l->b_p <= 0)
		return ;
	l->cur--;
	mines(l->cur_p, l);
}

void	delete(t_cmd *l)
{
	int	i;

	if (l->cur - l->b_p <= 0)
		return ;
	i = l->cur - 1;
	while (i < l->len)
	{
		l->chars[i] = l->chars[i + 1];
		i++;
	}
	l->len--;
	l->cur--;
	mines(l->cur_p, l);
}

void	down_k(t_cmd *l)
{
	if ((l->cur + l->w.ws_col) > l->len)
		return ;
	l->cur += l->w.ws_col;
	l->cur_p->r++;
}

void	up_k(t_cmd *l)
{
	int i;

	if ((l->cur - l->w.ws_col) < l->b_p)
		return ;
	i = l->w.ws_col + 1;
	while (--i > 0)
		mines(l->cur_p, l);
	l->cur -= l->w.ws_col;
}
