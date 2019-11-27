/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llachgar <llachgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 16:19:41 by hastid            #+#    #+#             */
/*   Updated: 2019/11/26 23:30:22 by llachgar         ###   ########.fr       */
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
		if (split_lines(line, &my_env) == -1)
			break ;
		ft_memdel((void **)&line);
	}
	ft_memdel((void **)&line);
	free_environ(my_env);
	return (0);
}
