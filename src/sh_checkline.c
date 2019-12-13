/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_checkline.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llachgar <llachgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 18:04:31 by hastid            #+#    #+#             */
/*   Updated: 2019/12/13 14:59:43 by llachgar         ###   ########.fr       */
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

char			*aff_prompt(char *str)
{
	int		ret;
	char	*cmdl;
	char	*temp;

	cmdl = read_line(str);
	if (!cmdl)
		return (0);
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
		else
			ret = ft_perror(0, "syntax error: unexpected end of file", -1);
	}
	if (!check_spacestr(cmdl))
		add_to_hist(ft_strdup(cmdl));
	if (ret == -1)
		return (ft_strdup("\0"));
	return (cmdl);
}
