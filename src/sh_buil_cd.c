/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_buil_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 16:29:59 by hastid            #+#    #+#             */
/*   Updated: 2019/11/23 16:51:49 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

int	built_cd(char **args, t_env **env)
{
	char	*tmp;
	char	*pwd;

	if (args[1])
	{
		if (isdir(args[1]))
		{
			tmp = getcwd(0, 0);
			add_elem(env, "OLDPWD", tmp);
			ft_memdel((void **)&tmp);
			add_elem(env, "PWD", args[1]);
			chdir(args[1]);
		}
		else if (!access(args[1], F_OK))
			ft_perror(args[1], ": Not a directory");
		else
			ft_perror(args[1], ": No such file or directory");
	}
	else if ((pwd = ft_getenv(*env, "HOME")))
	{
		tmp = getcwd(0, 0);
		add_elem(env, "OLDPWD", tmp);
		ft_memdel((void **)&tmp);
		add_elem(env, "PWD", pwd);
		chdir(pwd);
	}
	else
		ft_perror(0, ":Home not exists");
	return (0);
}
