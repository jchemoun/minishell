/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raw_mode.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchemoun <jchemoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 12:44:29 by jchemoun          #+#    #+#             */
/*   Updated: 2021/04/03 14:19:02 by jchemoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	enable_rawmode(void)
{
	struct termios	raw;

	tcgetattr(1, &raw);
	raw.c_lflag &= ~(ECHO | ICANON | ISIG);
	raw.c_cc[VMIN] = 0;
	raw.c_cc[VTIME] = 1;
	tcsetattr(1, TCSAFLUSH, &raw);
}

void	disable_rawmode(void)
{
	struct termios	deraw;

	tcgetattr(1, &deraw);
	deraw.c_lflag = 35387;
	deraw.c_cc[VMIN] = 1;
	deraw.c_cc[VTIME] = 0;
	tcsetattr(1, TCSAFLUSH, &deraw);
}
