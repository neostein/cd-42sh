/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llachgar <llachgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 06:48:48 by llachgar          #+#    #+#             */
/*   Updated: 2019/12/06 04:09:40 by llachgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_editing.h"

void	alt_a(t_cmd *l)
{
	t_hist	*hist;

	(void)l;
	hist = NULL;
	hist = save_hist(&hist);
	if (!hist)
		return ;
	if (hist->col >= 5)
		hist->col = 0;
	else
		hist->col++;
}

void	ctl_l(t_cmd *l)
{
	ft_putstr_fd(CL, 1);
	get_cur_pos(l->init_p);
}

void	show_prompt(t_cmd *l)
{
	t_hist			*hist;
	static char		*colors[6] = {
		GREEN,
		YELLO,
		BLUE,
		RED,
		WHITE,
		RESET
	};

	hist = NULL;
	hist = save_hist(&hist);
	ft_putstr(colors[hist->col]);
	ft_putstr_fd(l->prompt, 1);
	ft_putstr_fd("|->$ ", 1);
	ft_putstr(colors[5]);
}
