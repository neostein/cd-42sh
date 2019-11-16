/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 00:12:11 by hastid            #+#    #+#             */
/*   Updated: 2019/11/16 04:57:02 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_21sh.h"
#include <stdio.h>

t_data	*init_struct(void)
{
	t_data	*data;

	if (!(data = (t_data *)malloc(sizeof(t_data))))
		return (0);
	data->rd = 0;
	data->lst_rd = 0;
	return (data);
}

t_fd	*init_redirection(void)
{
	t_fd	*fd;

	fd = (t_fd *)malloc(sizeof(t_fd));
	fd->fdfirst = 0;
	fd->fdsecond = 0;
	fd->next = 0;
	return (fd);
}

int		check_redirection(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '>' || str[i] == '<')
			return (1);
		i++;
	}
	return (0);
}

int		save_redirections(t_fd **lst_rd, char *fir, int	val, char *sec)
{
	t_fd	*tmp_fd;

	if (*lst_rd)
	{
		tmp_fd = *lst_rd;
		while(tmp_fd->next)
			tmp_fd = tmp_fd->next;
		tmp_fd->next = init_redirection();
		tmp_fd = tmp_fd->next;
	}
	else
	{
		*lst_rd = init_redirection();
		tmp_fd = *lst_rd;
	}
	if (val == 5)
		tmp_fd->fdsecond = ft_atoi(sec);
	if (val == 3)
		tmp_fd->fdsecond = open(sec, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (val == 7)
		tmp_fd->fdsecond = open(sec, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (fir)
		tmp_fd->fdfirst = ft_atoi(fir);
	else
		tmp_fd->fdfirst = 1;
	return (0);
}

int		add_redirections(t_data *data, t_tok *toks)
{
	t_fd	*rd;
	t_tok	*prev;

	rd = 0;
	if (check_redirection(toks->token))
		save_redirections(&rd, 0, toks->val, toks->next->token);
	prev = toks;
	toks = toks->next;
	while (toks)
	{
		if (check_redirection(toks->token) && toks->next)
		{
			if (save_redirections(&rd, prev->val ? prev->token : 0, toks->val, toks->next->token))
				return (1);
		}
		prev = toks;
		toks = toks->next;
	}
	data->lst_rd = rd;
	/*
	while (rd)
	{
		printf("%d -- %d\n", rd->fdfirst, rd->fdsecond);	
		rd = rd->next;
	}
	*/
	return (0);
}

int		args_len(t_tok	*toks)
{
	int	i;

	i = 0;
	while (toks)
	{
		if (toks->val == 0)
			i++;
		toks = toks->next;
	}
	return (1);
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

char	*check_path(char *str)
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
	ft_putstr("21sh: command not found: ");
	ft_putendl(str);
	return (0);
}

int		add_args(t_data *data, t_tok *toks)
{
	int	i;

	if (!(data->args = (char **)malloc(sizeof(char *) * (args_len(toks) + 1))))
		return (1);
	i = 0;
	if (!(data->args[i++] = check_path(toks->token)))
		return (1);
	toks = toks->next;
	while (toks)
	{
		if (toks->val == 0)
			if (!(data->args[i++] = ft_strdup(toks->token)))
				return (1);
		toks = toks->next;
	}
	data->args[i] = 0;
	return (0);
}

int		sh_excute(t_data *data)
{
	int	in;
	int	out;
	int	err;
	int	pid;
	t_fd	*rd;

	in = dup(0);
	out = dup(1);
	err = dup(2);
	pid = fork();
	if (pid < 0)
		return (-1);
	if (pid == 0)
	{
		if (data->rd)
		{
			rd = data->lst_rd;
			while (rd)
			{
				printf("%d -- %d", rd->fdsecond, rd->fdfirst);
				dup2(rd->fdsecond, rd->fdfirst);
				rd = rd->next;
			}
		}
		execve(data->args[0], data->args, 0);
		return (0);
	}
	dup2(in, 0);
	dup2(out, 1);
	dup2(err, 2);
	waitpid(pid, 0, 0);
	return (1);
}

int		check_numbers(char *str)
{
	int	i;

	i = 0;

	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

int		check_token(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (check_spechar(str[i]))
			return (1);
		i++;
	}
	return (0);
}

int		val_token(char *str)
{
	int		i;
	int		be;
	int		count;

	i = 0;
	count = 1;
	while (str[i] != '>' || str[i] == '<')
		i++;
	be = i++;
	if (!str[i])
	{
		if (str[be] == '>')
			return (3);
		if (str[be] == '<')
			return (4);
	}
	if (str[i] == '&')
	{
		i++;
		if (str[i])
		{
			ft_putendl("error  1");
			return (-1);
		}
		if (str[be] == '>')
			return (5);
		if (str[be] == '<')
			return (6);

	}
	if (str[i++] != str[be])
	{
		ft_putendl("error  2");
		return (-1);
	}
	if (str[i])
	{
		ft_putendl("error  1");
		return (-1);
	}
	if (str[be] == '>')
		return (7);
	if (str[be] == '<')
		return (8);
	return (-1);
}

int		check_tokens(char *str)
{
	if (check_token(str))
		return (val_token(str));
	if (check_numbers(str))
		return (0);
	return (1);
}

int		edit_token(t_tok **toks)
{
	int		ret;
	t_tok	*tmp;

	ret = 0;
	tmp = *toks;
	while (tmp)
	{
		if (ret == 5 || ret == 6)
		{
			if (check_numbers(tmp->token))
			{
				ft_putendl("error 3");
				return (1);
			}
			else
				tmp->val = 2;
		}
		ret = 0;
		if (tmp->val == 1)
		{
			ret = check_tokens(tmp->token);
			tmp->val = ret;
			if(tmp->next && ret >= 3 && ret <= 8)
			{
				ret = 1;
				tmp->next->val = 1;
				tmp = tmp->next;
			}
		}
		if (ret == -1)
			return (1);
		if(ret >= 3 && ret <= 8)
			if (!(tmp->next) || tmp->next->token[0] == '\0')
			{
				ft_putendl("error 4");
				return (1);
			}
		tmp = tmp->next;
	}
	return (0);
}

int		save_data(char	*str)
{
	t_tok	*toks;
	t_data	*data;

	toks = split_token(str);

	if (edit_token(&toks))
		return (1);
	
	t_tok	*tmp;
	tmp = toks;
/*
	while (tmp)
	{
		printf("%d --- %s\n",tmp->val, tmp->token);
		tmp = tmp->next;
	}
*/
	if (!(data = init_struct()))
		return (1);

	if ((data->rd = check_redirection(str)))
		if (add_redirections(data, toks))
			return (1);

	if (add_args(data, toks))
		return (1);



	sh_excute(data);
/*			
	int i = 0;
	while (data->args[i])
		ft_putendl(data->args[i++]);
*/
	free_token(toks);
	return (0);
}

int		split_line(char *line)
{
	int		i;
	int		b;
	int		be;
	char	*tmp;

	i = 0;

	while (line[i])
	{
		while (line[i] && line[i] == ' ')
			i++;
		b = i;
		while (line[i] && line[i] != ';')
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
			save_data(tmp);
			ft_memdel((void **)&tmp);
		}
		i++;
	}
	return (0);
}

int		main()
{
	int		r;
	char	*tmp;
	char	buf[1337];

	while (1337)
	{
		ft_putstr("\033[1;31m");
		ft_putstr("my_21sh-3$ ");
		ft_putstr("\033[0m");
		r = read(0, buf, 1337);
		buf[r - 1] = '\0';
		tmp = ft_strdup(buf);
		if (split_line(tmp))
		{
			ft_putendl("by by");
			return (1);
		}
	}
	return (0);
}
