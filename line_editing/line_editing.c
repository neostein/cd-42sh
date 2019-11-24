/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_editing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llachgar <llachgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 06:44:47 by llachgar          #+#    #+#             */
/*   Updated: 2019/11/24 06:46:55 by llachgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_editing.h"

static char    *ft_strjoin_f(char *s1, char *s2, int a, int b)
{
	char	*str;
	int		len;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	if (!(str = ft_strnew(len)))
		return (NULL);
	ft_strcpy(str, (char *)s1);
	ft_strcat(str, (char *)s2);
	if (a)
		free(s1);
	if (b)
		free(s2);
	return (str);
}

char        *line_editing(char *promt)
{
	char *cmd;
	char *tmp;

	cmd = read_line(promt);
	while (ft_strlen(cmd) && (!q_closed(cmd) || !pipes_end(cmd)))
	{
		ft_putchar('\n');
		tmp = read_line("> ");
		cmd = ft_strjoin_f(cmd, tmp, 1, 1);
	}
    // here goes the haire dogs;) just like the test 
	return (cmd);
}