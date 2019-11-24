/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 08:51:53 by hastid            #+#    #+#             */
/*   Updated: 2019/11/24 08:52:09 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

int		main(int ac, char **av, char **env)
{
	char	*line;
	t_env	*my_env;

	my_env = creat_env(env);
	init_history();
	while (1337)
	{
		line = line_editing("21sh >$ ");
		ft_putchar('\n');
		add_to_hist(ft_strdup(line));
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
