/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 10:57:42 by jchemoun          #+#    #+#             */
/*   Updated: 2020/11/02 16:35:53 by user42           ###   ########.fr       */
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
	write(1, "\b\b  \b\b", 6);
	return ;
}

void		global_change(int signum)
{
	if (signum == 3)
		write(2, "Quit: 3", 7);
	write(1, "  \n", 3);
}
