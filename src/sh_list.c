/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_list.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 06:33:22 by hastid            #+#    #+#             */
/*   Updated: 2019/11/22 05:47:20 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

t_cmdl	*init_cmdl(void)
{
	t_cmdl	*cmdl;

	if (!(cmdl = (t_cmdl *)malloc(sizeof(t_cmdl))))
		return (0);
	cmdl->rd = 0;
	cmdl->lrd = 0;
	cmdl->excu = 0;
	cmdl->args = 0;
	return (cmdl);
}

t_tok	*init_token(char *tmp, int id)
{
	t_tok	*token;

	if (!(token = (t_tok *)malloc(sizeof(t_tok))))
		return (0);
	token->id = id;
	if (!(token->value = ft_strdup(tmp)))
		return (0);
	token->next = 0;
	return (token);
}

t_fd	*init_redirect(void)
{
	t_fd	*fd;

	if (!(fd = (t_fd *)malloc(sizeof(t_fd))))
		return (0);
	fd->fir = 0;
	fd->sec = 0;
	fd->next = 0;
	return (fd);
}

int		save_tokens(t_tok **tok, char *token, int id)
{
	t_tok	*tmp;

	if (*tok)
	{
		tmp = *tok;
		while (tmp->next)
			tmp = tmp->next;
		if (!(tmp->next = init_token(token, id)))
			return (1);
	}
	else if (!((*tok) = init_token(token, id)))
		return (1);
	return (0);
}
