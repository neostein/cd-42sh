/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_environ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 03:39:43 by hastid            #+#    #+#             */
/*   Updated: 2019/12/01 04:15:11 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

int		ft_unsetenv(t_env **env, char **args)
{
	int		i;

	i = 1;
	if (args[i])
	{
		while (args[i])
			del_elem(env, args[i++]);
	}
	else
		ft_perror(0, "Too few arguments.", 1);
	return (0);
}

int		ft_setenv(t_env **env, char **args)
{
	if (args[1])
		add_elem(env, args[1], args[2]);
	else
		ft_putenv(*env);
	return (0);
}

void	ft_putenv(t_env *env)
{
	while (env)
	{
		ft_putstr(env->name);
		ft_putchar('=');
		ft_putendl(env->value);
		env = env->next;
	}
}

char	*ft_getenv(t_env *env, char *name)
{
	while (env)
	{
		if (!ft_strcmp(name, env->name))
			return (env->value);
		env = env->next;
	}
	return (0);
}

t_env	*creat_env(char **env)
{
	int		i;
	int		co;
	char	*tmp;
	char	*name;
	t_env	*my_env;

	i = 0;
	my_env = 0;
	while (env && env[i])
	{
		tmp = env[i];
		co = 0;
		while (tmp[co] != '=')
			co++;
		name = ft_strsub(tmp, 0, co);
		add_to_env(&my_env, name, tmp + co + 1);
		ft_memdel((void **)&name);
		i++;
	}
	return (my_env);
}
