/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchemoun <jchemoun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 17:09:32 by jchemoun            #+#    #+#             */
/*   Updated: 2021/03/31 17:09:34 by jchemoun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <curses.h>
#include <term.h>
#include <termios.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void	enable_rawmode(void)
{
	struct termios	raw;

	tcgetattr(1, &raw);
	printf("LFLAG : %i\n", raw.c_lflag);
	raw.c_lflag &= ~(ECHO | ICANON);
	printf("LFLAG : %i\n", raw.c_lflag);
	printf("CCC VMIN : %i\nCCC VTIME : %i\n", raw.c_cc[VMIN], raw.c_cc[VTIME]);
	//raw.c_cc[VMIN] = 0;
	//raw.c_cc[VTIME] = 1;
	tcsetattr(1, TCSAFLUSH, &raw);
}

void	disable_rawmode(void)
{
	struct termios	deraw;

	tcgetattr(1, &deraw);
	deraw.c_lflag = 35387;
	tcsetattr(1, TCSAFLUSH, &deraw);
}

void	get_char(char *c, char **buf)
{
	read(1, c, 1);
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

char	*read_linev2(void)
{
	char	*buf;
	char	c;

	buf = calloc(1, 1);
	while (1)
	{
		get_char(&c, &buf);
		if (c == 10)
			return (buf);
		else if (c == 4)
		{
			if (*buf == 0)
			{
				disable_rawmode();
				write(1, "exit\n", 5);
				exit(0);
			}
		}
		else if (c == 127)
			ft_deappend(&buf);
		else if (c != 0 && c != 2 && c != 3 && c != 4)
			ft_append(&buf, c);
	}
	return (0);
}

void	crtl_bs(int signum)
{
	char	c;

	c = signum;
	write(0, &c, 1);
	write(1, "\b \b", 3);
	return ;
}

int	main(void)
{
	char *termtype = getenv("TERM");
	int success;
	char *term_buf = 0;
	printf("%s\n", termtype);
	if (termtype == 0)
		exit(1);
	success = tgetent(term_buf, termtype);
	printf("%i %s\n", success, term_buf);
	// 'le', 'nd' to move cursor
	// 'kr 'ku' etc for input arrow and etc
	// 'dc' or 'DC' to remove crt-\ signal
	enable_rawmode();
	signal(3, crtl_bs);
	signal(2, crtl_bs);
	char *line;
	line = read_linev2();
	printf("LINE : %s\n", line);
	free(line);
	disable_rawmode();
	return (0);
}
