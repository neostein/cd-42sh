/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 03:44:00 by hastid            #+#    #+#             */
/*   Updated: 2019/11/22 06:24:04 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

int		built_cmd(t_cmdl *cmdl)
{
	if (!ft_strcmp(cmdl->excu, "echo"))
		built_echo(cmdl->args);
	else
		return (1);
	return (0);
}

int		execute(t_cmdl *cmdl, char **env)
{
	if (!built_cmd(cmdl))
		exit(0);
	if (execve(cmdl->excu, cmdl->args, env) == -1)
		return (ft_perror(0, "exceve failed"));
	return (0);
}

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
				if (lrd->sec == -1)
					close(lrd->fir);
				else
					dup2(lrd->sec, lrd->fir);
				lrd = lrd->next;
			}
		}
		if (execute(cmdl, env))
			return (1);
	}
	if (pid > 0)
		wait(&pid);
	return (0);
}

t_cmdl	*save_to_excute(t_tok *toks)
{
	t_cmdl	*cmdl;

	if (!(cmdl = init_cmdl()))
		return (0);
	if ((cmdl->rd = add_redirections(cmdl, toks)) == -1)
		return (0);
	if (add_args(cmdl, toks))
	{
		free_cmdline(cmdl);
		return (0);
	}
	return (cmdl);
}

int		cmd_line(char *line, char **env)
{
	t_tok	*toks;
	t_cmdl	*cmdl;

	if (!(toks = split_tokens(line)))
		return (1);
	if (!(cmdl = save_to_excute(toks)))
	{
		free_tokens(toks);
		return (1);
	}
	if (execute_cmdl(cmdl, env))
	{
		free_cmdline(cmdl);
		free_tokens(toks);
		return (1);
	}
	free_cmdline(cmdl);
	free_tokens(toks);
	return (0);
}
