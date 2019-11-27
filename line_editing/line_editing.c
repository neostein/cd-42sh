/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_editing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llachgar <llachgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 06:44:47 by llachgar          #+#    #+#             */
/*   Updated: 2019/11/27 16:24:59 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_editing.h"

static int		check_redirect(char *str)
{
	int		i;
	int		ret;
	char	*rd;

	i = 0;
	ret = 0;
	while (check_spechar(str[i]))
		i++;
	rd = ft_strsub(str, 0, i);
	while (check_space(str[i]))
		i++;
	if (str[i])
	{
		if (!ft_strcmp(rd, ">") || !ft_strcmp(rd, "<"))
			ret = 1;
		if (!ft_strcmp(rd, ">>") || !ft_strcmp(rd, "<<") ||
				!ft_strcmp(rd, "<&") || !ft_strcmp(rd, "&>")
				|| !ft_strcmp(rd, "&<") || !ft_strcmp(rd, ">&"))
			ret = 2;
	}
	ft_memdel((void **)&rd);
	if (!ret)
		ret = ft_perror(0, " syntax error near unexpected token", 1);
	return (ret);
}

static char		*ft_strjoin_f(char *s1, char *s2, int a, int b)
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

static int		check_errline(char *str)
{
	int	i;
	int	ret;

	i = 0;
	while (str[i])
	{
		if (check_spechar(str[i]))
		{
			ret = check_redirect(str + i);
			if (ret == 0)
				return (1);
			i += ret;
		}
		i++;
	}
	return (0);
}

char			*line_editing(char *promt)
{
	char *cmd;
	char *tmp;

	cmd = read_line(promt);
	if (check_errline(cmd))
	{
		ft_memdel((void **)&cmd);
		return (ft_strdup("\0"));
	}
	while (cmd && ft_strlen(cmd) && (!q_closed(cmd) || !pipes_end(cmd)))
	{
		tmp = read_line("> ");
		cmd = ft_strjoin_f(cmd, "\n", 1, 0);
		cmd = ft_strjoin_f(cmd, tmp, 1, 1);
	}
	return (cmd);
}
