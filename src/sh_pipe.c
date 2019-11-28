/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 00:50:25 by hastid            #+#    #+#             */
/*   Updated: 2019/11/28 18:47:10 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"
#include <sys/wait.h>

static t_pipe	*add_pipe(t_cmdl *cmdl)
{
	t_pipe	*pi;

	if (!(pi = (t_pipe *)malloc(sizeof(t_pipe))))
		return (0);
	pi->cmdl = cmdl;
	pi->next = 0;
	return (pi);
}

static t_cmdl	*add_elem_cmdline(char *line, t_env *env)
{
	t_tok	*toks;
	t_cmdl	*cmdl;

	cmdl = 0;
	if ((toks = split_tokens(line)))
	{
		if (analy_toks(toks) || check_error(toks))
		{
			free_tokens(toks);
			return (0);
		}
		cmdl = save_to_excute(toks, env);
		free_tokens(toks);
	}
	return (cmdl);
}

static int		add_pipes(t_pipe **pipes, char *line, t_env *env)
{
	t_cmdl	*cmdl;
	t_pipe	*temp;

	if ((cmdl = add_elem_cmdline(line, env)))
	{
		if (!(*pipes))
		{
			if (!(*pipes = add_pipe(cmdl)))
				return (1);
		}
		else
		{
			temp = *pipes;
			while (temp->next)
				temp = temp->next;
			if (!(temp->next = add_pipe(cmdl)))
				return (1);
		}
	}
	else
		return (1);
	return (0);
}

static int		execut_bpipe(int inp, int pi[2], t_pipe *pipes, t_env **env)
{
	t_fd	*lrd;
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
	if (pipes->cmdl->rd)
	{
		lrd = pipes->cmdl->lrd;
		while (lrd)
		{
			if (lrd->sec == -1)
				close(lrd->fir);
			else if (dup2(lrd->sec, lrd->fir) == -1)
				return (ft_perror(0, "duplicate input failed", 1));
			lrd = lrd->next;
		}
	}
	execute_built(pipes->cmdl, env);
	free_file(fil);
	return (0);
}

static int		child_process(int inp, int pi[2], t_pipe *pipes, char **env)
{
	t_fd	*lrd;

	if (!inp)
		close(pi[0]);
	if (inp)
		if (dup2(inp, 0) == -1)
			return (ft_perror(0, "duplicate input failed", 1));
	if (inp)
		close(inp);
	if (pipes->next)
		if (dup2(pi[1], 1) == -1)
			return (ft_perror(0, "duplicate output failed", 1));
	close(pi[1]);
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
	char	**my_env;

	my_env = list_to_tab(env);
	if ((pid = fork()) == -1)
		return (ft_perror(0, "fork failed", 1));
	if (pid == 0)
		if (child_process(inp, pi, pipes, my_env))
			exit(1);
	free_tab(my_env);
	return (0);
}

static int		execute_pipe(t_pipe *pipes, t_env **env)
{
	int		inp;
	int		len;
	int		pi[2];

	inp = 0;
	len = 0;
	while (pipes)
	{
		if (ft_strcmp(pipes->cmdl->args[0], "exit"))
		{
			if (pipes->next)
				if (pipe(pi) == -1)
					return (ft_perror(0, "pipe failed", 1));
			if ((pipes->cmdl->excu = excutable(pipes->cmdl->args[0], *env)))
			{
				if (check_built(pipes->cmdl->excu))
					execut_bpipe(inp, pi, pipes, env);
				else if (fork_pipe(inp, pi, *env, pipes))
					return (1);
				len++;
			}
			if (inp)
				close(inp);
			inp = pi[0];
			close(pi[1]);
		}
		pipes = pipes->next;
	}
	while (len--)
		wait(0);
	return (0);
}

int				split_pipe(char *line, t_env **env)
{
	char	*tmp;
	t_pipe	*pipes;

	pipes = 0;
	while (*line)
	{
		while (*line && check_space(*line))
			line++;
		if (*line)
		{
			line = sub_line(&tmp, line, '|');
			if (tmp)
			{
				if (add_pipes(&pipes, tmp, *env))
				{
					ft_memdel((void **)&tmp);
					free_pipes(pipes);
					return (1);
				}
				ft_memdel((void **)&tmp);
			}
		}
	}
	execute_pipe(pipes, env);
	free_pipes(pipes);
	return (0);
}
