/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_list.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 01:28:02 by hastid            #+#    #+#             */
/*   Updated: 2019/11/09 04:31:57 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_21sh.h"

static t_tok	*add_elm(char *str, int to)
{
	t_tok	*elm;

	if (!(elm = (t_tok *)malloc(sizeof(t_tok))))
		return (0);
	if (!(elm->token = ft_strdup(str)))
		return (0);
	if (to == 1337)
		elm->val = 1;
	else
		elm->val = 0;
	elm->next = 0;
	return (elm);
}

int				add_to_list(t_tok **lst, char *str, int	to)
{
	t_tok	*tmp;

	if (*lst)
	{
		tmp = *lst;
		while (tmp->next)
			tmp = tmp->next;
		if (!(tmp->next = add_elm(str, to)))
			return (0);
	}
	else
	{
		if (!((*lst) = add_elm(str, to)))
			return (0);
	}
	return (1);
}

void			free_token(t_tok *lst)
{
	t_tok	*tmp;

	while (lst)
	{
		tmp = lst->next;
		ft_memdel((void **)&(lst->token));
		ft_memdel((void **)&lst);
		lst = tmp;
	}
}
