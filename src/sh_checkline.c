/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_checkline.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 18:04:31 by hastid            #+#    #+#             */
/*   Updated: 2019/12/18 01:39:48 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

char			*ft_strjoin_f(char *s1, char *s2, int a, int b)
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

static int		check_allerr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (check_spechar(str[i]))
		{
			while (check_spechar(str[i]))
				i++;
			while (check_space(str[i]))
				i++;
			while (ft_isdigit(str[i]))
				i++;
			if (check_spechar(str[i]))
				return (ft_perror(0, "syntax error near unexpected token", -1));
		}
		i++;
	}
	return (check_errline(str));
}

static int		check_aller(char *str)
{
	int	i;
	int	be;

	i = 0;
	if (str[0] == '|')
		return (ft_perror(0, "syntax error near unexpected token", -1));
	while (str[i])
	{
		if (str[i] == ';' || str[i] == '|')
		{
			be = i++;
			while (str[i] && check_space(str[i]))
				i++;
			if (str[i] == '|' || (str[i] == ';' && str[be] == '|'))
				return (ft_perror(0, "syntax error near unexpected token", -1));
		}
		else
			i++;
	}
	return (check_allerr(str));
}

char			*aff_prompt(t_env *env)
{
	int		ret;
	char	*cmdl;
	char	*temp;

	cmdl = prompt(env);
	if (!cmdl)
		return (0);
	ret = check_aller(cmdl);
	while (ret == 1 || ret == 2)
	{
		if ((temp = read_line(">")))
		{
			if (ret == 2)
				cmdl = ft_strjoin_f(cmdl, "\n", 1, 0);
			cmdl = ft_strjoin_f(cmdl, temp, 1, 1);
			ret = check_aller(cmdl);
		}
		else
			ret = ft_perror(0, "syntax error: unexpected end of file", -1);
	}
	if (!check_spacestr(cmdl))
		add_to_hist(ft_strdup(cmdl));
	if (ret == -1)
		return (ft_strdup("\0"));
	return (cmdl);
}
