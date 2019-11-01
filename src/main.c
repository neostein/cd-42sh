/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 11:43:23 by hastid            #+#    #+#             */
/*   Updated: 2019/11/01 00:13:07 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int		main()
{
	int		r;
	char	*tmp;
	char	buf[133];

	while (1)
	{
		ft_bzero(buf, 133);
		ft_putstr("------> ");
		r = read(0, buf, 133);
		buf[r - 1] = '\0';
		if (!ft_strcmp(buf, "exit"))
			break;
		tmp = ft_strdup(buf);
		split_line(tmp);
		ft_memdel((void **)&tmp);
	}
	return (0);
}
