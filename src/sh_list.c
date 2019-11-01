/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_list.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 23:53:18 by hastid            #+#    #+#             */
/*   Updated: 2019/11/01 00:04:41 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static t_arg	*add_elm(char *str)
{
	t_arg	*elm;

	if (!(elm = (t_arg *)malloc(sizeof(t_arg))))
		return (0);
	if (!(elm->str = ft_strdup(str)))
		return (0);
	elm->next = 0;
	return (elm);
}

int				add_to_list(t_arg **lst, char *str)
{
	t_arg	*tmp;

	if (*lst)
	{
		tmp = *lst;
		while (tmp->next)
			tmp = tmp->next;
		if (!(tmp->next = add_elm(str)))
			return (0);
	}
	else
	{
		if (!((*lst) = add_elm(str)))
			return (0);
	}
	return (1);
}

void			free_data(t_arg *lst)
{
	t_arg	*tmp;

	while (lst)
	{
		tmp = lst->next;
		ft_memdel((void **)&(lst->str));
		ft_memdel((void **)&lst);
		lst = tmp;
	}
}

void			free_tab(char **tab)
{
	int i;

	i = 0;
	if (tab)
	{
		while (tab[i])
			ft_memdel((void **)&tab[i++]);
		free(tab);
	}
}
