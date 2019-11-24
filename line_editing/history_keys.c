/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_keys.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llachgar <llachgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 15:43:00 by llachgar          #+#    #+#             */
/*   Updated: 2019/11/24 06:55:24 by llachgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_editing.h"

void	cur_stable(t_cmd *l, int i)
{
	if (i < l->len)
		while (i < l->len)
		{
			plus(l->cur_p, l, 0);
			i++;
		}
	else
		while (i > l->len)
		{
			mines(l->cur_p, l);
			i--;
		}
}

void	top_k(t_cmd *l)
{
	t_hist	*h;
	int		i;

	h = save_hist(NULL);
	if (h->hist[l->h_p + 1] == NULL)
		return ;
	if (l->h_p >= 14)
		return ;
	l->h_p++;
	if (l->h_p == 0)
		h->tmp = ft_strdup(l->chars);
	ft_strcpy(l->chars, h->hist[l->h_p]);
	i = l->cur;
	l->len = ft_strlen(h->hist[l->h_p]);
	l->cur = l->len;
	cur_stable(l, i);
}

void	bottom_k(t_cmd *l)
{
	t_hist	*h;
	int		i;

	h = save_hist(NULL);
	if (l->h_p <= -1)
		return ;
	l->h_p--;
	i = l->cur;
	if (l->h_p == -1)
	{
		ft_strcpy(l->chars, h->tmp);
		l->len = ft_strlen(h->tmp);
		free(h->tmp);
		h->tmp = NULL;
	}
	else
	{
		ft_strcpy(l->chars, h->hist[l->h_p]);
		l->len = ft_strlen(h->hist[l->h_p]);
	}
	l->cur = l->len;
	cur_stable(l, i);
}
