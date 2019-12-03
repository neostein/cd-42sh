/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 05:57:21 by hastid            #+#    #+#             */
/*   Updated: 2019/12/03 23:03:41 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

static int	built_echo(char **args)
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
			if (args[i + 1] && args[i] != '\0')
				ft_putstr(" ");
			i++;
		}
		if (check)
			ft_putchar('\n');
	}
	return (0);
}

int			check_built(char *str)
{
	if (!ft_strcmp(str, "cd"))
		return (1);
	if (!ft_strcmp(str, "env"))
		return (1);
	if (!ft_strcmp(str, "echo"))
		return (1);
	if (!ft_strcmp(str, "exit"))
		return (1);
	if (!ft_strcmp(str, "setenv"))
		return (1);
	if (!ft_strcmp(str, "unsetenv"))
		return (1);
	return (0);
}

int			execute_built(t_cmdl *cmdl, t_env **env)
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

int			built_cmd(t_cmdl *cmdl, t_env **env)
{
	t_fd	*lrd;
	t_file	*fil;

	if (check_built(cmdl->excu))
	{
		if (save_file(&fil, 0, 1, 2))
			exit(1);
		if (cmdl->rd)
		{
			lrd = cmdl->lrd;
			while (lrd)
			{
				if (lrd->sec == -1)
					close(lrd->fir);
				else if (dup2(lrd->sec, lrd->fir) == -1)
					return (ft_perror(0, "duplicate failed.", 0));
				lrd = lrd->next;
			}
		}
		execute_built(cmdl, env);
		free_file(fil);
	}
	else
		return (1);
	return (0);
}
