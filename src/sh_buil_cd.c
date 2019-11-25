/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_buil_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 16:29:59 by hastid            #+#    #+#             */
/*   Updated: 2019/11/24 10:53:01 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

int	built_cd(char **args, t_env **env)
{
	char	*tmp;
	char	*pwd;

	if (args[1])
	{
		if (!ft_strcmp("-", args[1]))
		{
			if ((pwd = ft_getenv(*env, "OLDPWD")))
			{
				tmp = getcwd(0, 0);
				add_elem(env, "PWD", pwd);
				add_elem(env, "OLDPWD", tmp);
				ft_memdel((void **)&tmp);
				chdir(pwd);
			}
			else
				ft_perror("env", ": Oldpwd not exists");
		}
		else if (isdir(args[1]))
		{
			tmp = getcwd(0, 0);
			add_elem(env, "OLDPWD", tmp);
			chdir(args[1]);
			ft_memdel((void **)&tmp);
			tmp = getcwd(0, 0);
			add_elem(env, "PWD", tmp);
			ft_memdel((void **)&tmp);
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
		ft_perror("env", ": Home not exists");
	return (0);
}
