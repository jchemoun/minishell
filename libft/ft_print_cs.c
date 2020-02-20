/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_cs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchemoun <jchemoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 16:33:36 by jchemoun          #+#    #+#             */
/*   Updated: 2019/11/19 16:58:56 by jchemoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <ft_printf.h>

static size_t	ft_strlenull(const char *s)
{
	size_t i;

	if (!s)
		return (6);
	i = 0;
	while (*(s + i))
		i++;
	return (i);
}

int				ft_print_string(int conv[N_FLAG], va_list pa)
{
	int		i;
	int		j;
	char	*str;
	char	buf[ft_abs(conv[2]) + ft_strlenull(str = va_arg(pa, char*))];

	i = 0;
	j = 0;
	str = (!str) ? "(null)" : str;
	conv[3] < 0 ? conv[3] = (int)ft_strlen(str) : 0;
	if (conv[1] < 0 || conv[2] < 0)
	{
		while (str[j] && i < conv[3])
			buf[i++] = str[j++];
		while ((unsigned)i < ft_abs(conv[2]))
			buf[i++] = ' ';
	}
	else
	{
		while (i < ft_min(ft_abs(conv[2]), ft_abs(conv[2]) -
			ft_min((int)ft_strlen(str), conv[3])))
			buf[i++] = ' ';
		while (str[j] && j < conv[3])
			buf[i++] = str[j++];
	}
	return ((int)write(1, buf, i));
}

int				ft_print_pc(int conv[N_FLAG], va_list pa)
{
	int				i;
	int				range;
	unsigned char	buf[ft_abs(conv[2]) + 1];

	(void)pa;
	i = 0;
	range = ft_abs(conv[2]);
	if (conv[1] < 0 || conv[2] < 0)
	{
		buf[i++] = '%';
		while (i < range)
			buf[i++] = ' ';
	}
	else
	{
		while (i < range - 1)
			buf[i++] = (conv[1] == 0) ? '0' : ' ';
		buf[i++] = '%';
	}
	return ((int)write(1, buf, i));
}

int				ft_print_char(int conv[N_FLAG], va_list pa)
{
	int				i;
	int				range;
	unsigned char	buf[ft_abs(conv[2]) + 1];

	i = 0;
	range = ft_abs(conv[2]);
	if (conv[1] < 0 || conv[2] < 0)
	{
		buf[i++] = va_arg(pa, int);
		while (i < range)
			buf[i++] = ' ';
	}
	else
	{
		while (i < range - 1)
			buf[i++] = ' ';
		buf[i++] = va_arg(pa, int);
	}
	return ((int)write(1, buf, i));
}
