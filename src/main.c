/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 01:21:51 by hastid            #+#    #+#             */
/*   Updated: 2019/11/23 15:13:00 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"
#include <fcntl.h>

int		main(int ac, char **av, char **env)
{
	char	*line;
	t_env	*my_env;

	my_env = creat_env(env);
	while (1337)
	{
		line = readline("21sh >$ ");
//		printf("%d\n", open(av[1], O_RDONLY));
		add_history(line);
		if (!ft_strcmp(line, "exit"))
		{
			ft_memdel((void **)&line);
			break ;
		}
		split_lines(line, &my_env);
		ft_memdel((void **)&line);
	}
	return (0);
}
