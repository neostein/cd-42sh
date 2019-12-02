/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_buil_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 16:29:59 by hastid            #+#    #+#             */
/*   Updated: 2019/12/02 02:28:53 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

static int	change_dir(char *dir, t_env **env)
{
	char	*pwd;

	if ((pwd = getcwd(0, 0)))
	{
		add_elem(env, "OLDPWD", pwd);
		ft_memdel((void **)&pwd);
		chdir(dir);
		if ((pwd = getcwd(0, 0)))
		{
			add_elem(env, "PWD", pwd);
			ft_memdel((void **)&pwd);
		}
	}
	return (0);
}

int			built_cd(char **args, t_env **env)
{
	char	*dir;

	if (args[1])
	{
		if (!ft_strcmp("-", args[1]))
		{
			if ((dir = ft_getenv(*env, "OLDPWD")))
				change_dir(dir, env);
			else
				ft_perror("env", ": Oldpwd not exists", 1);
		}
		else if (isdir(args[1]))
			change_dir(args[1], env);
		else if (!access(args[1], F_OK))
			ft_perror(args[1], ": Not a directory", 1);
		else
			ft_perror(args[1], ": No such file or directory", 1);
	}
	else if ((dir = ft_getenv(*env, "HOME")))
		change_dir(dir, env);
	else
		ft_perror("env", ": Home not exists", 1);
	return (0);
}
