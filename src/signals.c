/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchemoun <jchemoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 10:57:42 by jchemoun          #+#    #+#             */
/*   Updated: 2021/04/03 14:21:39 by jchemoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	signal_callback_handler(int signum)
{
	char	c;

	c = signum;
	write(1, &c, 1);
	write(1, "\b \b", 3);
	g_ret = 1;
}

void	sign3(int signum)
{
	char	c;

	c = signum;
	write(0, &c, 1);
	write(1, "\b \b", 3);
	return ;
}

void	global_change(int signum)
{
	if (signum == 3)
		write(2, "Quit: 3", 7);
	write(1, "  \n", 3);
}

void	crtl_d_exit(void)
{
	disable_rawmode();
	write(2, "exit\n", 5);
	exit(0);
}

void	crtl_c_buf(char **buf)
{
	free(*buf);
	*buf = ft_calloc(1, 1);
	ft_printf("^C\n> ");
}
