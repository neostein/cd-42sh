/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llachgar <llachgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 13:13:47 by llachgar          #+#    #+#             */
/*   Updated: 2019/11/24 06:55:24 by llachgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_editing.h"

void		default_term_mode(void)
{
	struct termios	tattr;

	tcgetattr(STDIN_FILENO, &tattr);
	tattr.c_lflag |= (ECHO | ICANON);
	tattr.c_oflag |= (OPOST);
	tcsetattr(STDIN_FILENO, TCSADRAIN, &tattr);
}

void		read_key(t_cmd *l)
{
	int		res;
	char	buff[READ_SIZE];
	int		i;

	res = read(0, buff, READ_SIZE);
	ft_bzero(buff + res, 3);
	i = -1;
	while (buff[++i] && ft_isprint(buff[i]))
	{
		l->key = buff[i];
		add_at(l);
	}
	l->key = 0;
	if (res <= 4)
		l->key = *(int *)buff;
}

void		print_cmd(t_cmd *l)
{
	t_point	p;
	int		i;

	i = l->b_p - 1;
	p.r = l->init_p->r - 1;
	p.c = ft_strlen(l->prompt);
	ft_putstr_fd(tgoto(CM, 0, l->init_p->r - 1), 0);
	ft_putstr_fd(CD, 0);
	ft_putstr_fd(l->prompt, 0);
	while (++i < l->len)
	{
		if (i == (l->cur - l->s_sp) && l->is_s)
			ft_putstr_fd(SO, 0);
		if (i == l->cur && l->is_s)
			ft_putstr_fd(SE, 0);
		ft_putchar_fd(l->chars[i], 0);
		plus(&p, l, 1);
	}
	ft_putstr_fd(tgoto(CM, l->cur_p->c, l->cur_p->r), 0);
	ft_putstr_fd(SE, 0);
}

void		match_key(t_cmd *l)
{
	int				i;
	static t_key	keys[17] = {
		{RIGHT_K, &right_key},
		{LEFT_K, &left_key},
		{ESC_K, &esc_key},
		{BACK_K, &delete},
		{END_K, &end_k},
		{HOME_K, &home_k},
		{INTER_K, &return_k},
		{CTL_B, &ctl_left},
		{CTL_F, &ctl_right},
		{UP_K, &up_k},
		{DOWN_K, &down_k},
		{ALT_L_K, &alt_l_k},
		{ALT_U_K, &alt_u_k},
		{ALT_D_K, &alt_d_k},
		{ALT_X_K, &alt_x_k},
		{TOP_K, &top_k},
		{BOTTOM_K, &bottom_k}
	};

	i = -1;
	while (++i < 17)
		if (l->key == keys[i].key)
			keys[i].f(l);
}

char		*read_line(char *prompt)
{
	t_cmd			*l;
	struct winsize	w;
	char			*result;

	init_term();
	if ((l = init_cmd(prompt)) == NULL)
		return (0);
	keep_l(l);
	while (l->res)
	{
		read_key(l);
		match_key(l);
		print_cmd(l);
		if (l->is_s == 0)
			l->s_sp = 0;
		l->is_s = 0;
	}
	default_term_mode();
	result = ft_strdup(l->chars);
	bzero(l->chars, BUFF_SIZE);
	free(l->cur_p);
	free(l->init_p);
	free(l);
	return (result);
}
