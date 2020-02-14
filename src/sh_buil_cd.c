/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_buil_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaber <nsaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 16:29:59 by hastid            #+#    #+#             */
/*   Updated: 2020/02/14 22:12:12 by nsaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"
#include <sys/stat.h>

static int	change_dir_b(char *dir, t_env **env)
{
	char	*pwd;
	chdir(dir);
	if ((pwd = getcwd(0, 0)))
	{
		add_elem(env, "OLDPWD", pwd);
		add_elem(env, "PWD", pwd);
		ft_memdel((void **)&pwd);
	}
	return (0);
}

static int	change_dir_a(char *dir, t_env **env)
{
	char	*tp;
	char	*pwd;

	if ((tp = ft_getenv(*env, "PWD")))
	{
		if (!(pwd = ft_strdup(tp)))
			return (0);
	}
	else if (!(pwd = getcwd(0, 0)))
		return (0);
	if ((tp = path_of_link(dir, pwd)))
	{
		chdir(tp);
		// printf("olwdpwd = %s\n",pwd);
		add_elem(env, "OLDPWD", pwd);
		add_elem(env, "PWD", tp);
		ft_memdel((void **)&tp);
	}
	else
		return (0);
	ft_memdel((void **)&pwd);
	return (1);
}

static int	change_dir(char *dir, t_env **env)
{
	if (!change_dir_a(dir, env))
		change_dir_b(dir, env);
	return (0);
}

char		*read_link(char *tmp)
{
	static char mybuf[PATH_MAX];

	ft_bzero(mybuf,PATH_MAX);
	readlink(tmp,mybuf,PATH_MAX);
	return(mybuf);
}

int		built_cd_p(char **args, t_env **env,char *dir, char *tmp)
{
	struct stat buf;
	char *mybuf; // noureddine

	if (args[2] && lstat(args[2], &buf) == -1) // should show here and error, folder not found or permission denied
		return(0);
	if ((buf.st_mode & S_IFMT) == S_IFLNK && isdir(args[2]))
	{
		// change_dir(args[2], env);
		// chdir(args[2]);
		if (args[2][0] != '/')
		{
			if (!(dir = ft_getenv(*env, "PWD")))
				return (ft_perror("env", ": pwd not exists", 1));
			dir = ft_strjoin(dir,"/");
			tmp = ft_strjoin(dir, args[2]);
			free(dir);
			mybuf = read_link(tmp);
			// printf("inside mybuf : %s \n",mybuf);
			free(tmp);
		}
		else
			mybuf = read_link(args[2]);
		if (args[2][0] == '/' && S_ISLNK(buf.st_mode) && mybuf[0] != '/' )
		{
			chdir(args[2]);
		}
		// printf("mybuf : %s \n",mybuf);
		change_dir(mybuf, env);
	}
	else
		built_cd(args+1, env);
	return(0);
}

int			arraylen(char **args)
{
	int i;

	i = 0;
	while(args && *args)
	{
		args++;
		i++;
	}
	return(i);
}

int			built_cd(char **args, t_env **env)
{
	char	*dir;
	int 	len;

	len = arraylen(args);
	// printf("len : %d \n",len);
	if (args[1] && ft_strequ(args[1], "-P")) // noureddine
		built_cd_p(args, env,NULL,NULL);
	else if (args[1] && ft_strequ(args[1], "-L")) 
		built_cd(args+1, env);
	else if (args[1])
	{
		if (!ft_strcmp("-", args[1]))
		{
			if (!(dir = ft_getenv(*env, "OLDPWD")))
				return (ft_perror("env", ": Oldpwd not exists", 1));
		}
		else
			dir = args[1];
		if (isdir(dir))
			change_dir(dir, env);
		else if (!access(dir, F_OK) && access(dir,X_OK))
			ft_perror(dir, ": Permission Denied", 1);
		else if (!access(dir, F_OK))
			ft_perror(dir, ": Not a directory", 1);
		else
			ft_perror(dir, ": No such file or directory", 1);
	}
	else if ((dir = ft_getenv(*env, "HOME")))
		change_dir(dir, env);
	else
		ft_perror("env", ": Home not exists", 1);
	return (0);
}
