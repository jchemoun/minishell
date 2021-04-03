/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entry.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchemoun <jchemoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 17:09:32 by jchemoun          #+#    #+#             */
/*   Updated: 2021/04/03 13:02:59 by jchemoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	get_char(char *c, char **buf, t_historia_dc **historia)
{
	char	termc[2];

	while (read(0, c, 1) != 1)
		;
	if (*c == '\e')
	{
		read(0, &termc[0], 1);
		if (termc[0] == '[')
		{
			read(0, &termc[1], 1);
			if (termc[1] == 65)
				arrow_up(buf, historia);
			else if (termc[1] == 66)
				arrow_down(buf, historia);
			else if (termc[1] == 67)
				arrow_lr(buf);
			else if (termc[1] == 68)
				arrow_lr(buf);
		}
	}
	return ;
}

void	ft_append(char **buf, char c)
{
	int		i;
	int		j;
	char	*nbuf;

	i = 0;
	while (*(*buf + i))
		i++;
	nbuf = malloc(i + 2);
	j = 0;
	while (j < i)
	{
		nbuf[j] = *(*buf + j);
		j++;
	}
	nbuf[j] = c;
	nbuf[j + 1] = 0;
	free(*buf);
	*buf = nbuf;
	write(1, &c, 1);
}

void	ft_deappend(char **buf)
{
	int		i;
	int		j;
	char	*nbuf;

	i = 0;
	while (*(*buf + i))
		i++;
	if (i == 0)
		return ;
	nbuf = malloc(i);
	j = 0;
	while (j < i - 1)
	{
		nbuf[j] = *(*buf + j);
		j++;
	}
	free(*buf);
	nbuf[j] = 0;
	*buf = nbuf;
	write(1, "\b \b", 3);
}

char	*read_linev2(t_historia_dc **historia)
{
	char	*buf;
	char	c;

	buf = ft_calloc(1, 1);
	ft_printf("> ");
	while (1)
	{
		get_char(&c, &buf, historia);
		if (c == 10)
		{
			write(1, "\n", 1);
			return (buf);
		}
		else if (c == 3)
			crtl_c_buf(&buf);
		else if (c == 4 && *buf == 0)
			crtl_d_exit();
		else if (c == 127)
			ft_deappend(&buf);
		else if (ft_isprint(c))
			ft_append(&buf, c);
	}
	return (0);
}
