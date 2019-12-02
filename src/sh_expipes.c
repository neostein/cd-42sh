/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_expipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 03:31:09 by hastid            #+#    #+#             */
/*   Updated: 2019/12/02 02:59:42 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

static int		execut_b(t_cmdl *cmdl, t_env **env)
{
	t_fd	*lrd;

	if (cmdl->rd)
	{
		lrd = cmdl->lrd;
		while (lrd)
		{
			if (lrd->sec == -1)
				close(lrd->fir);
			else if (dup2(lrd->sec, lrd->fir) == -1)
				return (ft_perror(0, "duplicate input failed", 1));
			lrd = lrd->next;
		}
	}
	execute_built(cmdl, env);
	return (0);
}

static int		execut_bpipe(int inp, int pi[2], t_pipe *pipes, t_env **env)
{
	t_file	*fil;

	if (save_file(&fil, 0, 1, 2))
		return (1);
	if (dup2(inp, 0) == -1)
		return (ft_perror(0, "duplicate input failed", 1));
	close(inp);
	if (pipes->next)
		if (dup2(pi[1], 1) == -1)
			return (ft_perror(0, "duplicate input failed", 1));
	close(pi[1]);
	if (execut_b(pipes->cmdl, env))
	{
		free_file(fil);
		return (1);
	}
	free_file(fil);
	return (0);
}

static int		child_process(t_pipe *pipes, char **env)
{
	t_fd	*lrd;

	if (pipes->cmdl->rd)
	{
		lrd = pipes->cmdl->lrd;
		while (lrd)
		{
			if (lrd->sec == -3)
				close(lrd->fir);
			else if (dup2(lrd->sec, lrd->fir) == -1)
				return (ft_perror(0, "duplicate output failed", 1));
			lrd = lrd->next;
		}
	}
	if (execve(pipes->cmdl->excu, pipes->cmdl->args, env) == -1)
		return (ft_perror(0, "execve output failed", 1));
	return (0);
}

static int		fork_pipe(int inp, int pi[2], t_env *env, t_pipe *pipes)
{
	int		pid;
	int		ret;
	char	**my_env;

	ret = 0;
	my_env = list_to_tab(env);
	if ((pid = fork()) == -1)
		return (ft_perror(0, "fork failed", 1));
	if (pid == 0)
	{
		if (inp)
			if (dup2(inp, 0) == -1)
				ret = ft_perror(0, "duplicate input failed", 1);
		inp ? close(inp) : close(pi[0]);
		if (pipes->next)
			if (dup2(pi[1], 1) == -1)
				ret = ft_perror(0, "duplicate output failed", 1);
		close(pi[1]);
		if (ret || child_process(pipes, my_env))
			exit(1);
	}
	free_tab(my_env);
	return (0);
}

int				execute_p(int inp, int pi[2], t_env **env, t_pipe *pipes)
{
	if ((pipes->cmdl->excu = excutable(pipes->cmdl->args[0], *env)))
	{
		if (check_built(pipes->cmdl->excu))
		{
			if (execut_bpipe(inp, pi, pipes, env))
				return (1);
		}
		else if (fork_pipe(inp, pi, *env, pipes))
			return (1);
	}
	if (inp)
		close(inp);
	close(pi[1]);
	return (0);
}
