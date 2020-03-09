/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchemoun <jchemoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 10:57:42 by jchemoun          #+#    #+#             */
/*   Updated: 2020/03/09 11:41:42 by jchemoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void		signal_callback_handler(int signum)
{
	(void)signum;
	write(1, "\b\b  ", 4);
	ft_printf("\n> ");
	g_ret = 1;
}

void		sign3(int signum)
{
	(void)signum;
	write(0, "\b\b  ", 4);
	return ;
}

void		global_change(int signum)
{
	if (signum == 3)
		write(2, "Quit: 3", 7);
	write(1, "  \n", 3);
}
