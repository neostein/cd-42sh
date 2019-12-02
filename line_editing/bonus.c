/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llachgar <llachgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 06:48:48 by llachgar          #+#    #+#             */
/*   Updated: 2019/12/02 03:37:12 by llachgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_editing.h"

void	ctl_l(t_cmd *l)
{
	ft_putstr_fd(CL, 1);
	get_cur_pos(l->init_p);
}

void	show_prompt(t_cmd *l)
{
	ft_putstr("\e[0;32m");
	ft_putstr_fd(l->prompt, 1);
	ft_putstr_fd("|->$ ", 1);
	ft_putstr("\e[39m");
}
