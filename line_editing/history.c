/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llachgar <llachgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 19:39:13 by llachgar          #+#    #+#             */
/*   Updated: 2019/11/19 16:40:23 by llachgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_editing.h"

void	init_history(void)
{
	t_hist	*hist;
	int		i;

	hist = (t_hist *)malloc(sizeof(t_hist));
	hist->tmp = NULL;
	i = 0;
	while (i < 15)
	{
		hist->hist[i] = NULL;
		i++;
	}
	save_hist(hist);
}

void	add_and_sheft(t_hist *hist, char *cmd)
{
	int i;

	i = 15;
	if (hist->hist[14] != NULL)
		free(hist->hist[14]);
	while (--i > 0)
		hist->hist[i] = hist->hist[i - 1];
	hist->hist[0] = cmd;
}

void	add_to_hist(char *cmd)
{
	t_hist *hist;

	if (ft_strlen(cmd) == 0)
		return ;
	hist = save_hist(NULL);
	add_and_sheft(hist, cmd);
}
