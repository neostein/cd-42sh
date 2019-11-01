/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_pipes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 02:16:19 by hastid            #+#    #+#             */
/*   Updated: 2019/11/01 05:37:48 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

t_pipe	*add_elem(char **args, int read, int	write, int rfd)
{
	t_pipe	*elem;

	if (!(elem = (t_pipe *)malloc(sizeof(t_pipe))))
		return (0);
	elem->r = read;
	elem->w = write;
	elem->fd = rfd;
	elem->args = args;
	elem->next = 0;
	return (elem);
}

int		add_list(t_pipe **pipes, char **args ,int read, int write, int rfd)
{
	t_pipe	*tmp;

	if (*pipes)
	{
		tmp = *pipes;
		while(tmp->next)
			tmp = tmp->next;
		tmp->next = add_elem(args, read, write, rfd);
	}
	else
		(*pipes) = add_elem(args, read, write, rfd);
	return (1);
}

int		ret_redirection(int *r, int *w, int *fd, t_arg *tmp)
{
	while (tmp)
	{
		if ((ft_strchr(tmp->str, '>')))
		{
			if (tmp->next)
			{
				if (ft_strstr(tmp->str, ">>"))
					*fd = open(tmp->next->str, O_WRONLY | O_APPEND | O_CREAT, 0644);
				else
					*fd = open(tmp->next->str, O_WRONLY | O_TRUNC | O_CREAT, 0644);
				*w = 1;
				*r = 0;
			}
			else
				ft_putendl("21sh: parse error near '\\n'");
		}
		if ((ft_strchr(tmp->str, '<')))
		{
			if (tmp->next)
			{
				*fd = open(tmp->next->str, O_RDONLY);
				*w = 0;
				*r = 1;
			}
			else
				ft_putendl("21sh: parse error near '\\n'");
		}
		tmp = tmp->next;
	}
	return (1);
}

int		pipe_redirection(t_pipe **pipes, t_arg *lst)
{
	int		i;
	int		l;
	int		r;
	int		w;
	int		fd;
	char	*tp;
	char	**as;
	t_arg	*tmp;

	l = 0;
	tmp = lst;
	if (!(tp = check_head(lst->str)))
		return (0);
	while (tmp)
	{
		if (ft_strchr(tmp->str, '>') || ft_strchr(tmp->str, '<'))
			break ;
		l++;
		tmp = tmp->next;
	}
	as = (char **)malloc(sizeof(char *) * (l + 1));
	i = 0;
	as[i++] = tp;
	tmp = lst->next;
	while (i < l)
	{
		as[i++] = ft_strdup(tmp->str);
		tmp = tmp->next;
	}
	as[i] = 0;
	ret_redirection(&r, &w, &fd, tmp);
	add_list(pipes, as, r, w, fd);
	return (1);
}

int		save_pipes(t_pipe **pipes, t_arg *lst, int red)
{
	int		i;
	char	*tp;
	char	**as;
	t_arg	*tmp;

	i = 0;
	tmp = lst;
	if (!red)
	{
		if (!(tp = check_head(lst->str)))
			return (0);
		while (tmp)
		{
			i++;
			tmp = tmp->next;
		}
		as = (char **)malloc(sizeof(char *) * (i + 1));
		i = 0;
		as[i++] = tp;
		tmp = lst->next;
		while (tmp)
		{
			as[i++] = ft_strdup(tmp->str);
			tmp = tmp->next;
		}
		as[i] = 0;
		add_list(pipes, as, 0, 0, 0);
	}
	else
		pipe_redirection(pipes, lst);
	return (1);
}

int		split_blank_pipes(char *line, t_pipe **pipes)
{
	int		i;
	int		b;
	int		be;
	int		rdi;
	char	*tmp;
	t_arg	*lst;

	i = 0;
	rdi = 0;
	lst = 0;
	while (line[i])
	{
		while (line[i] && line[i] == ' ')
			i++;
		b = i;
		while (line[i] && line[i] != ' ')
		{
			if (line[i] == 34 || line[i] == 39)
			{
				be = i++;
				while (line[i] && line[i] != line[be])
					i++;
			}
			if (line[i] == '>' || line[i] == '<')
				rdi = 1;
			i++;
		}
		if (i - b > 0)
		{
			if (!(tmp = ft_strsub(line, b, i - b)))
				return (0);
			if (!add_to_list(&lst, tmp))
				return (0);
			ft_memdel((void **)&tmp);
		}
	}
	if (!save_pipes(pipes, lst, rdi))
		return (0);;
	free_data(lst);
	return (1);
}

int		excute_pipes(t_pipe *pipes)
{
	int pid;
	int	cont;
	int pfd[2];

	while (pipes)
	{
		if (pipe(pfd) < 0)
			return -1;
		pid = fork();
		if (pid < 0)
			return -1;
		else if (pid == 0) /*son code*/
		{
			if (pipes->w)
				dup2(pipes->fd, 1);
			else if (pipes->next)
				dup2(pfd[1], 1);
			if (pipes->r)
				dup2(pipes->fd, 0);
			else
				dup2(cont,0);
			close(pfd[1]);
			close(pfd[0]);
			execve(pipes->args[0], pipes->args, 0);
			return 0;
		}
		waitpid(pid, 0, 0);
		close(pfd[1]);
		cont = pfd[0];
		pipes = pipes->next;
	}
	close(pfd[1]);
	return (1);
}


int		split_pipes(char *line)
{
	int		i;
	int		b;
	int		be;
	char	*tmp;
	t_pipe	*pipes;

	i = 0;
	pipes = 0;

	while (line[i])
	{
		while (line[i] && line[i] == ' ')
			i++;
		b = i;
		while (line[i] && line[i] != '|')
		{
			if (line[i] == 34 || line[i] == 39)
			{
				be = i++;
				while (line[i] && line[i] != line[be])
					i++;
			}
			i++;
		}
		if (i - b > 0)
		{
			if (!(tmp = ft_strsub(line, b, i - b)))
				return (0);
			if (!split_blank_pipes(tmp, &pipes))
				return (0);
			ft_memdel((void **)&tmp);
		}
		i++;
	}
	/*
	   while (pipes)
	   {
	   i = 0;
	   while (pipes->args[i])
	   ft_putendl(pipes->args[i++]);
	   pipes = pipes->next;
	   }
	   */
	excute_pipes(pipes);
	return (1);
}
