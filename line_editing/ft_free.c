/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llachgar <llachgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 05:39:04 by llachgar          #+#    #+#             */
/*   Updated: 2019/11/26 05:46:19 by llachgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_editing.h"

void	free_out(t_cmd *l)
{
	bzero(l->chars, BUFF_SIZE);
	free(l->cur_p);
	free(l->init_p);
	free(l);
	keep_l(NULL, 0);
}
