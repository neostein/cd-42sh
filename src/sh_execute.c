/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 03:44:00 by hastid            #+#    #+#             */
/*   Updated: 2019/11/24 11:14:16 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"
#include <signal.h>

int		execute_cmdl(t_cmdl *cmdl, char **env)
{
	int		pid;
	t_fd	*lrd;

	if ((pid = fork()) == -1)
		return (ft_perror(0, "fork failed"));
	if (pid == 0)
	{
		if (cmdl->rd)
		{
			lrd = cmdl->lrd;
			while (lrd)
			{
				if (lrd->sec == -3)
					close(lrd->fir);
				else
					dup2(lrd->sec, lrd->fir);
				lrd = lrd->next;
			}
		}
		if (execve(cmdl->excu, cmdl->args, env) == -1)
			return (ft_perror(0, "exceve failed"));
	}
	if (pid > 0)
		wait(&pid);
	return (0);
}

char	**list_to_tab(t_env *env)
{
	int		i;
	char	**en;
	char	*temp;
	t_env	*tmp;

	i = 0;
	tmp = env;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	en = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (env)
	{
		temp = ft_strjoin(env->name, "=");
		en[i++] = ft_strjoin(temp, env->value);
		ft_memdel((void **)&temp);
		env = env->next;
	}
	en[i] = 0;
	return (en);
}

int		execute(t_cmdl *cmdl, t_env **env)
{
	char	**my_env;

	if (!built_cmd(cmdl, env))
		return (0);
	else
	{
		my_env = list_to_tab(*env);
		execute_cmdl(cmdl, my_env);
		free_tab(my_env);
	}
	return (0);
}

t_cmdl	*save_to_excute(t_tok *toks, t_env *env)
{
	t_cmdl	*cmdl;

	if (!(cmdl = init_cmdl()))
		return (0);
	if ((cmdl->rd = add_redirections(cmdl, toks)) == -1)
		return (0);
	if (add_args(cmdl, toks, env))
	{
		free_cmdline(cmdl);
		return (0);
	}
	return (cmdl);
}

int		cmd_line(char *line, t_env **env)
{
	t_tok	*toks;
	t_cmdl	*cmdl;

	if (!(toks = split_tokens(line)))
		return (1);
	if (!(cmdl = save_to_excute(toks, *env)))
	{
		free_tokens(toks);
		return (1);
	}
	if (execute(cmdl, env))
	{
		free_cmdline(cmdl);
		free_tokens(toks);
		return (1);
	}
	free_tokens(toks);
	free_cmdline(cmdl);
	return (0);
}
