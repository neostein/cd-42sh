/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 00:50:25 by hastid            #+#    #+#             */
/*   Updated: 2019/11/26 14:15:35 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"
#include <sys/wait.h>

t_pipe	*add_pipe(t_cmdl *cmdl)
{
	t_pipe	*pi;

	if (!(pi = (t_pipe *)malloc(sizeof(t_pipe))))
		return (0);
	pi->cmdl = cmdl;
	pi->next = 0;
	return (pi);
}

int		add_pipes(t_pipe **pipes, char *line, t_env *env)
{
	t_tok	*toks;
	t_cmdl	*cmdl;
	t_pipe	*temp;

	if (!(toks = split_tokens(line)))
		return (1);
	if (!(cmdl = save_to_excute(toks, env)))
		return (1);
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
	free_tokens(toks);
	return (0);
}

int		execut_built_pipe(int inp, int outp, t_pipe *pipes, t_env **env)
{
	int		in;
	int		out;
	int		err;
	t_fd	*lrd;

	in = dup(0);
	out = dup(1);
	err = dup(2);
	if (dup2(inp, 0) == -1)
		return (ft_perror(0, "duplicate input failed"));
	close(inp);
	if (pipes->next)
		if (dup2(outp, 1) == -1)
			return (ft_perror(0, "duplicate output failed"));
	close(outp);
	if (pipes->cmdl->rd)
	{
		lrd = pipes->cmdl->lrd;
		while (lrd)
		{
			if (lrd->sec == -1)
				close(lrd->fir);
			else
				dup2(lrd->sec, lrd->fir);
			lrd = lrd->next;
		}
	}
	execute_built(pipes->cmdl, env);
	dup2(in, 0);
	dup2(out, 1);
	dup2(err, 2);
	close(in);
	close(out);
	close(err);
	return (0);
}

int		child_process(int inp, int out, t_pipe *pipes, char **env, int p0)
{
	t_fd	*lrd;

	if (!inp)
		close(p0);
	if (dup2(inp, 0) == -1)
		return (ft_perror(0, "duplicate input failed"));
	close(inp);
	if (pipes->next)
		if (dup2(out, 1) == -1)
			return (ft_perror(0, "duplicate output failed"));
	close(out);
	if (pipes->cmdl->rd)
	{
		lrd = pipes->cmdl->lrd;
		while (lrd)
		{
			if (lrd->sec == -3)
				close(lrd->fir);
			else
				dup2(lrd->sec, lrd->fir);
			lrd = lrd->next;
		}
	}
	execve(pipes->cmdl->excu, pipes->cmdl->args, env);
	return (0);
}

int		execute_pipe(t_pipe *pipes, t_env **env)
{
	int		pid;
	int		inp;
	int		len;
	int		pi[2];
	char	**my_env;

	inp = 0;
	len = 0;
	while (pipes)
	{
		if (ft_strcmp(pipes->cmdl->excu, "exit") && pipes->next && pipe(pi) == -1)
			return (ft_perror(0, "pipe failed"));
		if (check_built(pipes->cmdl->excu) && ft_strcmp(pipes->cmdl->excu, "exit"))
			execut_built_pipe(inp, pi[1], pipes, env);
		else if (ft_strcmp(pipes->cmdl->excu, "exit"))
		{
			my_env = list_to_tab(*env);
			if ((pid = fork()) == -1)
				return (ft_perror(0, "fork failed"));
			if (pid == 0)
				if (child_process(inp, pi[1], pipes, my_env, pi[0]))
					return (1);
		}
		if (inp)
			close(inp);
		inp = pi[0];
		close(pi[1]);
		len++;
		pipes = pipes->next;
	}
	while (len--)
		wait(&pid);
	return (0);
}

int		split_pipe(char *line, t_env **env)
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
			if (!(line = sub_line(&tmp, line, '|')))
				return (1);
			if (add_pipes(&pipes, tmp, *env))
				return (1);
			ft_memdel((void **)&tmp);
		}
	}
	if (execute_pipe(pipes, env))
		return (1);
	free_pipes(pipes);
	return (0);
}
