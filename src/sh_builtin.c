/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 05:57:21 by hastid            #+#    #+#             */
/*   Updated: 2019/11/24 10:54:16 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

int		built_echo(char **args)
{
	int i;
	int check;

	if (args[1] == NULL)
		ft_putchar('\n');
	else
	{
		i = 1;
		check = 1;
		if (!ft_strcmp("-n", args[1]))
		{
			i = 2;
			check = 0;
		}
		while (args[i])
		{
			ft_putstr(args[i]);
			if (args[i][0] != '\0')
				ft_putstr(" ");
			i++;
		}
		if (check)
			ft_putchar('\n');
	}
	return (0);
}

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
		ft_perror(0, "Too few arguments.");
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

int		check_built(char *str)
{
	if (!ft_strcmp(str, "cd"))
		return (1);
	if (!ft_strcmp(str, "env"))
		return (1);
	if (!ft_strcmp(str, "echo"))
		return (1);
	if (!ft_strcmp(str, "setenv"))
		return (1);
	if (!ft_strcmp(str, "unsetenv"))
		return (1);
	return (0);
}

int		execute_built(t_cmdl *cmdl, t_env **env)
{
	if (!ft_strcmp(cmdl->excu, "cd"))
		built_cd(cmdl->args, env);
	if (!ft_strcmp(cmdl->excu, "env"))
		ft_putenv(*env);
	if (!ft_strcmp(cmdl->excu, "echo"))
		built_echo(cmdl->args);
	if (!ft_strcmp(cmdl->excu, "setenv"))
		ft_setenv(env, cmdl->args);
	if (!ft_strcmp(cmdl->excu, "unsetenv"))
		ft_unsetenv(env, cmdl->args);
	return (0);
}

int		built_cmd(t_cmdl *cmdl, t_env **env)
{
	int		in;
	int		out;
	int		err;
	t_fd	*lrd;

	if (check_built(cmdl->excu))
	{
		in = dup(0);
		out = dup(1);
		err = dup(2);
		if (cmdl->rd)
		{
			lrd = cmdl->lrd;
			while (lrd)
			{
				if (lrd->sec == -1)
					close(lrd->fir);
				else
					dup2(lrd->sec, lrd->fir);
				lrd = lrd->next;
			}
		}
		execute_built(cmdl, env);
		dup2(in, 0);
		dup2(out, 1);
		dup2(err, 2);
		close(in);
		close(out);
		close(err);
	}
	else
		return (1);
	return (0);
}
