/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llachgar <llachgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 15:47:01 by llachgar          #+#    #+#             */
/*   Updated: 2019/11/24 06:55:24 by llachgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_editing.h"

t_cmd	*keep_l(t_cmd *l)
{
	static t_cmd *tmp;

	if (l == NULL)
		return (tmp);
	tmp = l;
	return (l);
}

t_hist	*save_hist(t_hist *hist)
{
	static t_hist *tmp;

	if (hist == NULL)
		return (tmp);
	tmp = hist;
	return (hist);
}
