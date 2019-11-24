/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llachgar <llachgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 18:33:26 by llachgar          #+#    #+#             */
/*   Updated: 2019/11/24 06:55:24 by llachgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_editing.h"

t_cmd		*init_cmd(char *prompt)
{
	t_cmd *l;

	l = (t_cmd *)malloc(sizeof(t_cmd));
	l->init_p = (t_point *)malloc(sizeof(t_point));
	l->cur_p = (t_point *)malloc(sizeof(t_point));
	if (l == NULL || l->init_p == NULL || l->cur_p == NULL)
		return (NULL);
	l->prompt = prompt;
	ft_putstr_fd(l->prompt, 0);
	get_cur_pos(l->init_p);
	get_cur_pos(l->cur_p);
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &(l->w));
	l->len = 0;
	l->b_p = 0;
	l->cur_p->c--;
	l->cur_p->r--;
	l->cur = 0;
	l->hist = NULL;
	l->cpy[0] = 0;
	l->is_s = 0;
	l->s_sp = 0;
	l->res = 1337;
	l->h_p = -1;
	return (l);
}

void		init_term(void)
{
	char			*termtype;
	int				success;
	struct termios	tattr;

	termtype = getenv("TERM");
	if (termtype == 0)
		ft_putstr_fd("Specify a terminal type'.\n", 2);
	success = tgetent(0, termtype);
	if (success < 0)
		ft_putstr_fd("Could not access the termcap data base.\n", 2);
	if (success == 0)
		ft_putstr_fd("Terminal type  is not defined.\n", 2);
	if (termtype == 0 || success <= 0)
		exit(0);
	tcgetattr(STDIN_FILENO, &tattr);
	tattr.c_lflag &= ~(ICANON | ECHO);
	tattr.c_oflag &= ~(OPOST);
	tcsetattr(STDIN_FILENO, TCSANOW, &tattr);
}
