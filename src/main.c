/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llachgar <llachgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 01:21:51 by hastid            #+#    #+#             */
/*   Updated: 2019/11/26 00:41:24 by llachgar         ###   ########.fr       */
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
		if (!line)
			exit(0);
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
