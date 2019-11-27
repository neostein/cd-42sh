/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llachgar <llachgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 16:19:41 by hastid            #+#    #+#             */
/*   Updated: 2019/11/27 20:44:07 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

void	kill_seg(int seg)
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
		ft_perror(0, " syntax error near unexpected token", 1);
	return (ret);
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
		else
			i++;
	}
	return (0);
}

int		main(int ac, char **av, char **env)
{
	char	*line;
	t_env	*my_env;

	signal(SIGINT, kill_seg);
	my_env = creat_env(env);
	init_history();
	while (1337)
	{
		if (!(line = line_editing("21sh >$ ")))
			break ;
		add_to_hist(ft_strdup(line));
		if (!check_errline(line))
			if (split_lines(line, &my_env) == -1)
				break ;
		ft_memdel((void **)&line);
	}
	ft_memdel((void **)&line);
	free_environ(my_env);
	return (0);
}
