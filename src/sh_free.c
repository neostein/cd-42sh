/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 03:56:42 by hastid            #+#    #+#             */
/*   Updated: 2019/12/04 00:13:15 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

void	free_tab(char **tab)
{
	int i;

	i = 0;
	if (tab)
	{
		while (tab[i])
			ft_memdel((void **)&tab[i++]);
		ft_memdel((void **)&tab);
	}
}

void	free_pipes(t_pipe *lst)
{
	t_pipe	*tmp;

	while (lst)
	{
		tmp = lst->next;
		free_cmdline(lst->cmdl);
		ft_memdel((void **)&lst);
		lst = tmp;
	}
}

void	free_tokens(t_tok *lst)
{
	t_tok	*tmp;

	while (lst)
	{
		tmp = lst->next;
		ft_memdel((void **)&(lst->value));
		ft_memdel((void **)&lst);
		lst = tmp;
	}
}

void	free_cmdline(t_cmdl *cmdl)
{
	t_fd	*lrd;

	if (!cmdl)
		return ;
	if (cmdl->rd)
	{
		while (cmdl->lrd)
		{
			lrd = cmdl->lrd->next;
			if (cmdl->lrd->fir != 0 && cmdl->lrd->fir
					!= 1 && cmdl->lrd->fir != 2)
				close(cmdl->lrd->fir);
			if (cmdl->lrd->sec != 0 && cmdl->lrd->sec!= 1
					&& cmdl->lrd->sec != 2  && cmdl->lrd->sec != -3)
				close(cmdl->lrd->sec);
			ft_memdel((void**)&(cmdl->lrd));
			cmdl->lrd = lrd;
		}
	}
	if (cmdl->excu)
		ft_memdel((void**)&(cmdl->excu));
	if (cmdl->args)
		free_tab(cmdl->args);
	ft_memdel((void**)&cmdl);
}

void	free_environ(t_env *lst)
{
	t_env	*tmp;

	while (lst)
	{
		tmp = lst->next;
		ft_memdel((void **)&(lst->name));
		ft_memdel((void **)&(lst->value));
		ft_memdel((void **)&lst);
		lst = tmp;
	}
}
