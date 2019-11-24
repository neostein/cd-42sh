/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_manage.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llachgar <llachgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 15:17:56 by llachgar          #+#    #+#             */
/*   Updated: 2019/11/24 06:55:24 by llachgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_editing.h"

void	alt_l_k(t_cmd *l)
{
	l->is_s = 1;
	if (l->cur - l->s_sp <= l->b_p)
		return ;
	l->s_sp++;
}

void	alt_d_k(t_cmd *l)
{
	int i;

	if (ft_strlen(l->cpy) == 0)
		return ;
	i = 0;
	while (l->cpy[i])
	{
		l->key = l->cpy[i];
		add_at(l);
		i++;
	}
}

void	alt_u_k(t_cmd *l)
{
	int i;
	int min;
	int max;

	if (!l->s_sp)
		return ;
	min = l->cur - l->s_sp;
	max = l->cur;
	i = 0;
	while (min <= max)
		l->cpy[i++] = l->chars[min++];
	l->cpy[i] = 0;
}

void	alt_x_k(t_cmd *l)
{
	int i;
	int min;
	int max;
	int avg;

	if (!l->s_sp)
		return ;
	alt_u_k(l);
	min = l->cur - l->s_sp;
	max = l->cur;
	avg = max - min;
	avg++;
	i = min - 1;
	while (++min < l->len)
		l->chars[min] = l->chars[min + avg];
	if (l->cur != i)
		while (avg && l->cur != l->b_p)
		{
			mines(l->cur_p, l);
			l->len--;
			l->cur--;
			avg--;
		}
}
