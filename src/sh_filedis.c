/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_filedis.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:42:58 by hastid            #+#    #+#             */
/*   Updated: 2019/11/27 19:45:53 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

int		save_file(t_file **file, int in, int out, int err)
{
	if (!((*file) = (t_file *)malloc(sizeof(t_file))))
		return (1);
	(*file)->in = dup(in);
	(*file)->out = dup(out);
	(*file)->err = dup(err);
	return (0);
}

void	free_file(t_file *file)
{
	if (file)
	{
		dup2(file->in, 0);
		dup2(file->out, 1);
		dup2(file->err, 2);
		close(file->in);
		close(file->out);
		close(file->err);
		ft_memdel((void **)&file);
	}
}
