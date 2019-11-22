/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 21:29:59 by hastid            #+#    #+#             */
/*   Updated: 2019/11/22 05:27:38 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

int		ft_perror(char *s, char *str)
{
	ft_putstr("21sh: ");
	if (s)
		ft_putstr(s);
	ft_putendl(str);
	return (1);
}

int		ft_error_0(char *val)
{
	int	fd;

	fd = ft_atoi(val);
	if (dup2(1, fd) == -1)
		return (ft_perror(val, ": Bad file descriptor"));
	if (fd != 0 && fd != 1 && fd != 2)
		close(ft_atoi(val));
	return (0);
}

int		ft_error_1(char *val, int id, int n)
{
	int			f;
	struct stat	s;

	if (id != 2)
	{
		if (val[0] == '\0')
		{
			if (n == 6)
				return (ft_perror("1", ": Bad file descriptor"));
			if (n == 9)
				return (ft_perror("0", ": Bad file descriptor"));
		}
		if (n == 9)
			return (ft_perror(val, ": ambiguous redirect"));
	}
	if (id == 2)
	{
		if (fstat(f = ft_atoi(val), &s) == -1)
			return (ft_perror(val, ": Bad file descriptor"));
		if (n == 6 && write(f, 0, 0) == -1)
			return (ft_perror(val, ": Permission denied"));
		if (n == 9 && read(f, 0, 0) == -1)
			return (ft_perror(val, ": Permission denied"));
	}
	return (0);
}

int		ft_error_2(char *val, int id, int n)
{
	if (val[0] == '\0')
		return (ft_perror(val, ": No such file or directory"));
	if ((n == 5 || n == 7 || n == 11) && !access(val, F_OK))
		if (access(val, W_OK) == -1)
			return (ft_perror(val, ": Permission denied"));
	if ((n == 8 || n == 12) && access(val, F_OK) == -1)
		return (ft_perror(val, ": No such file or directory"));
	if ((n == 8 || n == 12) && !access(val, F_OK))
		if (access(val, R_OK) == -1)
			return (ft_perror(val, ": Permission denied"));
	return (0);
}

int		check_error(t_tok *toks)
{
	int	id;

	while (toks)
	{
		id = 0;
		if (toks->id == 14)
			if (ft_error_0(toks->value))
				return (1);
		if (toks->id > 4 && toks->id < 13)
		{
			id = toks->id;
			if ((id == 6 || id == 9))
				if (ft_error_1(toks->next->value, toks->next->id, id))
					return (1);
			if (id == 5 || id == 7 || id == 8 || id == 11 || id == 12)
				if (ft_error_2(toks->next->value, toks->next->id, id))
					return (1);
		}
		toks = toks->next;
	}
	return (0);
}
