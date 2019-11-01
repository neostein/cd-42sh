/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_excute.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 01:20:27 by hastid            #+#    #+#             */
/*   Updated: 2019/11/01 03:49:02 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"
/*to delet*/
#include <stdio.h>

char		*check_head(char *str)
{
	int		i;
	char	*tmp;
	char	**path;

	i = 0;
	path = ft_strsplit("/usr/bin/:/bin/:/usr/sbin/:/sbin/:/usr/local/bin/:/usr/local/munki/", ':');
	while (path[i])
	{
		tmp = ft_strjoin(path[i], str);
		if (!access(tmp, F_OK))
		{
			free_tab(path);
			return (tmp);
		}
		ft_memdel((void **)&tmp);
		i++;
	}
	free_tab(path);
	printf("21sh: command not found: %s\n", str);
	return (0);
}

static int	excute_process(char **args, int read, int write, int rfd)
{
	int	pid;
	int	save_std;

	pid = fork();
	if (pid < 0)
		return (-1);
	if (pid == 0)
	{
		if (write || read)
		{
			if (write)
				dup2(rfd, 1);
			else
				dup2(rfd, 0);
			close(rfd);
		}
		execve(args[0], args, 0);
		return (0);
	}
	waitpid(pid, 0, 0);
	free_tab(args);
	if (write || read)
		close(rfd);
	return (1);
}

int			excute_args(t_arg *lst)
{
	int		i;
	char	**t;
	char	*tmp;
	t_arg	*temp;

	i = 0;
	temp = lst;
	if (!(tmp = check_head(lst->str)))
		return (0);
	while (temp)
	{
		i++;
		temp = temp->next;
	}
	t = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	t[i++] = tmp;
	temp = lst->next;
	while (temp)
	{
		t[i++] = ft_strdup(temp->str);
		temp = temp->next;
	}
	t[i] = 0;
	return (excute_process(t, 0, 0, 0));
}

int			excute_now(t_arg *lst)
{
	int		r;
	int		fd;
	int		pfd[2];
	char	buf[1337];

	pipe(pfd);
	if (!ft_strcmp(lst->str, ">"))
		if (lst->next && (fd = open(lst->next->str, O_WRONLY | O_APPEND | O_CREAT, 0644)) > 0)
			while ((r = read(1, buf, 1337)) > 0)
			{
				buf[r] = '\0';
				ft_putstr_fd(buf, fd);
			}
	if (!ft_strcmp(lst->str, "<"))
		if (lst->next && (fd = open(lst->next->str, O_RDONLY)) > 0)
			while ((r = read(fd, buf, 1337)) > 0)
			{
				buf[r] = '\0';
				ft_putstr(buf);
			}
	return (0);
}

int			add_redirection(char **args, t_arg *lst)
{
	int		fd;
	t_arg	*temp;

	temp = lst;
	while (temp)
	{
		if ((ft_strchr(temp->str, '>')))
		{
			if (temp->next)
			{
				if (ft_strstr(temp->str, ">>"))
					fd = open(temp->next->str, O_WRONLY | O_APPEND | O_CREAT, 0644);
				else
					fd = open(temp->next->str, O_WRONLY | O_TRUNC | O_CREAT, 0644);
				excute_process(args, 0, 1, fd);
				close(fd);
			}
			else
				ft_putendl("21sh: parse error near '\\n'");
		}
		if ((ft_strchr(temp->str, '<')))
		{
			if (temp->next)
			{
				fd = open(temp->next->str, O_RDONLY);
				excute_process(args, 1, 0, fd);
				close(fd);
			}
			else
				ft_putendl("21sh: parse error near '\\n'");
		}
		temp = temp->next;
	}
	return (1);
}

int			excute_redirections(t_arg *lst)
{
	int		i;
	int		l;
	char	*tmp;
	char	*rdi;
	char	**args;
	t_arg	*temp;

	l = 0;
	temp = lst;
	while (temp)
	{	
		if (ft_strchr(temp->str, '>') || ft_strchr(temp->str, '<'))
			break ;
		l++;
		temp = temp->next;
	}
	if (lst->next && temp == lst)
		return (excute_now(lst));
	if (!(tmp = check_head(lst->str)))
		return (0);
	args = (char **)malloc(sizeof(char *) * (l + 1));
	i = 0;
	args[i++] = tmp;
	temp = lst->next;
	while (i < l)
	{
		args[i++] = ft_strdup(temp->str);
		temp = temp->next;
	}
	args[i] = 0;
	add_redirection(args, temp);
	return (1);
}
