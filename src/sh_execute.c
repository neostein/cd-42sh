/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 03:44:00 by hastid            #+#    #+#             */
/*   Updated: 2019/11/22 03:16:28 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

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
		if (execve(cmdl->excu, cmdl->args, env) == -1)
			return (ft_perror(0, "exceve failed"));
	}
	if (pid > 0)
		wait(&pid);
	return (0);
}
