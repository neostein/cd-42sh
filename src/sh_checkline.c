/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_checkline.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 18:04:31 by hastid            #+#    #+#             */
/*   Updated: 2019/12/01 02:01:48 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

static int		check_valtok(char c)
{
	if (check_spechar(c) || c == '|')
		return (0);
	return (1);
}

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
	if (str[i] && check_valtok(str[i]))
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
		ft_perror(0, " syntax error near unexpected token", 1);
	return (ret);
}

static int		check_quotes(char *str, char q)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (str[i] == q)
			return (i);
		i++;
	}
	return (0);
}

static int		after_pipe(char *str)
{
	int	i;

	i = 0;
	if (str[i])
	{
		while (check_space(str[i]))
			i++;
		if (str[i])
			return (0);
	}
	return (1);
}

static int		check_errline(char *str)
{
	int	ret;

	while (*str)
	{
		if (check_spechar(*str))
		{
			if ((ret = check_redirect(str)) == 0)
				return (-1);
			str += ret;
		}
		else if (*str == 34 || *str == 39)
		{
			if ((ret = check_quotes(str, *str)) == 0)
				return (2);
			str += ret + 1;
		}
		else if (*str == '|')
		{
			if ((ret = after_pipe(++str)))
				return (ret);
		}
		else
			str++;
	}
	return (0);
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

int				check_spacestr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		if (!check_space(str[i++]))
			return (0);
	return (1);
}

char			*aff_prompt(char *str)
{
	int		ret;
	char	*cmdl;
	char	*temp;

	cmdl = read_line(str);
	if (cmdl)
	{
		ret = check_errline(cmdl);
		while (ret == 1 || ret == 2)
		{
			if ((temp = read_line(">")))
			{
				if (ret == 2)
					cmdl = ft_strjoin_f(cmdl, "\n", 1, 0);
				cmdl = ft_strjoin_f(cmdl, temp, 1, 1);
				ret = check_errline(cmdl);
			}
		}
		if (!check_spacestr(cmdl))
			add_to_hist(ft_strdup(cmdl));
		if (ret == -1)
			return (ft_strdup("\0"));
	}
	return (cmdl);
}
