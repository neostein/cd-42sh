/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_cmdline.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 16:20:06 by hastid            #+#    #+#             */
/*   Updated: 2019/12/01 04:12:12 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

static int	heredirect(char *fin)
{
	int		pi[2];
	char	*s2;
	char	*tmp;
	char	*file;

	file = 0;
	s2 = read_line(">");
	if (pipe(pi) == -1)
		return (ft_perror(0, "fork failed", -1));
	while (fin && s2 && ft_strcmp(fin, s2))
	{
		if (!(tmp = add_to_file(file, s2)))
			return (1);
		file = tmp;
		ft_memdel((void **)&s2);
		s2 = read_line(">");
	}
	ft_memdel((void **)&s2);
	if (file)
		write(pi[1], file, ft_strlen(file));
	ft_memdel((void **)&file);
	close(pi[1]);
	return (pi[0]);
}

static int	ret_fildis(int rd, char *file, int n_id)
{
	if ((rd == 6 || rd == 9) && n_id != 1)
		return (!ft_strcmp(file, "-") ? -3 : ft_atoi(file));
	else if (rd == 5 || (rd == 6 && n_id == 1) || rd == 11)
		return (open(file, O_WRONLY | O_TRUNC | O_CREAT, 0644));
	else if (rd == 8 || (rd == 9 && n_id == 1) || rd == 12)
		return (open(file, O_RDONLY));
	else if (rd == 7)
		return (open(file, O_WRONLY | O_APPEND | O_CREAT, 0644));
	else if (rd == 10)
		return (heredirect(file));
	return (-1);
}

static t_fd	*add_redirect(char *fd, int rd, char *file, int n_id)
{
	t_fd	*lrd;

	if (!(lrd = init_redirect()))
		return (0);
	if ((lrd->sec = ret_fildis(rd, file, n_id)) == -1)
	{
		ft_perror(0, "open failed", 0);
		return (0);
	}
	if (fd)
		lrd->fir = ft_atoi(fd);
	else if (rd == 5 || rd == 6 || rd == 7)
		lrd->fir = 1;
	else if (rd == 8 || rd == 9 || rd == 10)
		lrd->fir = 0;
	return (lrd);
}

static int	add_to_list(t_cmdl *cmdl, char *fd, int id, t_tok toks)
{
	t_fd	*lrd;

	if (cmdl->lrd)
	{
		lrd = cmdl->lrd;
		while (lrd->next)
			lrd = lrd->next;
		if (!(lrd->next = add_redirect(fd, id, toks.value, toks.id)))
			return (1);
	}
	else if (!(cmdl->lrd = add_redirect(fd, id, toks.value, toks.id)))
		return (1);
	return (0);
}

int			add_redirections(t_cmdl *cmdl, t_tok *toks)
{
	char	*fd;

	fd = 0;
	while (toks)
	{
		if (toks->id == 14)
			fd = toks->value;
		if (toks->id > 4 && toks->id < 13)
		{
			if (toks->id == 11 || toks->id == 12 ||
					((toks->id == 6 || toks->id == 9) && !fd))
				fd = (toks->id == 11 || toks->id == 6) ? "1" : "0";
			if (add_to_list(cmdl, fd, toks->id, *(toks->next)))
				return (0);
			if (toks->id == 11 || toks->id == 12 ||
					((toks->id == 6 || toks->id == 9) && !fd))
				if (add_to_list(cmdl, "2", toks->id, *(toks->next)))
					return (0);
			fd = 0;
		}
		toks = toks->next;
	}
	return ((cmdl->lrd == 0) ? 0 : 1);
}
