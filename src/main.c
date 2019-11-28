/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llachgar <llachgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 16:19:41 by hastid            #+#    #+#             */
/*   Updated: 2019/11/28 16:51:35 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

void			kill_seg(int seg)
{
	t_cmd	*l;
	char	buf[2];

	(void)seg;
	l = NULL;
	l = keep_l(l, 1);
	if (l != NULL)
	{
		l->res = 0;
		l->ctl_c = 1;
		buf[0] = -62;
		buf[1] = 0;
		ioctl(0, TIOCSTI, buf);
	}
	ft_putchar('\n');
}

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
		if (str[i] && !check_valtok(str[i]))
			return (ft_perror(0, " syntax error near unexpected token", -1));
		else if (str[i])
			return (0);
	}
	return (1);
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
				return (-1);
			i += ret;
		}
		else if (str[i] == 34 || str[i] == 39)
		{
			ret  = check_quotes(str + i, str[i]);
			if (!ret)
				return (2);
			i += ret + 1;
		}
		else if (str[i] == '|')
		{
			i++;
			ret = after_pipe(str +  i);
			if (ret)
				return (ret);
		}
		else
			i++;
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

static char		*aff_prompt(char *str)
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
				cmdl = ft_strjoin_f(cmdl, temp, 1, 1) ;
				ret = check_errline(cmdl);
			}
		}
		add_to_hist(ft_strdup(cmdl));
		if (ret == -1)
			return (ft_strdup("\0"));
	}
	return (cmdl);
}

int				main(int ac, char **av, char **env)
{
	char	*line;
	t_env	*my_env;

	signal(SIGINT, kill_seg);
	my_env = creat_env(env);
	init_history();
	while (1337)
	{
		if (!(line = aff_prompt("21sh >$ ")))
			break ;
		if (!check_errline(line))
			if (split_lines(line, &my_env) == -1)
				break ;
		ft_memdel((void **)&line);
	}
	ft_memdel((void **)&line);
	free_environ(my_env);
	return (0);
}
