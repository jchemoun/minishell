/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_nbr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchemoun <jchemoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 16:24:12 by jchemoun          #+#    #+#             */
/*   Updated: 2019/11/19 16:59:26 by jchemoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <ft_printf.h>

int			ft_snbr(long long int n, char *b)
{
	int i;
	int	bl;

	bl = (int)ft_strlen(b);
	i = 0;
	while (n != 0)
	{
		n = n / bl;
		i++;
	}
	return (i);
}

static int	ft_nbr0(long long int n, int field, int form, char *b)
{
	int		i;
	int		power;
	char	buf[field + 1];

	i = 0;
	power = ((n == 0) ? ft_snbr(n, b) + 1 : ft_snbr(n, b));
	if (n < 0 && form == 0)
		buf[i++] = '-';
	while (i < (field - power) - (n < 0 && form))
		buf[i++] = ((form == 0) ? '0' : ' ');
	if (n < 0 && form != 0)
		buf[i++] = '-';
	return (write(1, buf, i) + ft_putnbr_base(ft_abs(n), b));
}

static int	ft_nbrp(long long int n, int field, int prec, char *b)
{
	int		i;
	int		j;
	int		power;
	char	buf_s[field + 1];
	char	buf_0[ft_abs(prec)];

	i = 0;
	j = 0;
	power = ((n == 0) ? 1 - !prec : ft_snbr(n, b));
	n < 0 ? field-- : 0;
	while (i < prec - power)
		buf_0[i++] = '0';
	while (j < field - (ft_max(prec, power)))
		buf_s[j++] = ' ';
	if (n < 0)
	{
		buf_s[j++] = '-';
		return (write(1, buf_s, j) + write(1, buf_0, i) +
			ft_putnbr_base(-n, b));
	}
	else if (prec == 0 && n == 0)
		return (write(1, buf_s, j));
	else
		return (write(1, buf_s, j) + write(1, buf_0, i) + ft_putnbr_base(n, b));
}

static int	ft_nbrm(long long int n, int field, int prec, char *b)
{
	int		i;
	int		j;
	int		power;
	char	buf_s[field];
	char	buf_0[ft_abs(prec) + 1];

	i = 0;
	j = 0;
	power = ((n == 0) ? 1 - !prec : ft_snbr(n, b));
	(n < 0) ? buf_0[i++] = 45 : 0;
	i ? prec++ : 0;
	while (i < prec - power)
		buf_0[i++] = '0';
	while (j < field - (power + i))
		buf_s[j++] = ' ';
	if (n < 0)
	{
		return (write(1, buf_0, i) + ft_putnbr_base(-n, b) +
			write(1, buf_s, j));
	}
	else if (prec == 0 && n == 0)
		return (write(1, buf_s, j));
	else
		return (write(1, buf_0, i) + ft_putnbr_base(n, b) + write(1, buf_s, j));
}

int			ft_print_nbr(int conv[N_FLAG], va_list pa)
{
	long long int	n;
	signed char		sc;

	if (conv[4] == 0)
		n = va_arg(pa, int);
	else if (conv[4] == 1)
		n = va_arg(pa, long int);
	else if (conv[4] == 2)
		n = va_arg(pa, long long int);
	else if (conv[4] == -1)
		n = (short)va_arg(pa, int);
	else if (conv[4] == -2)
	{
		sc = (signed char)va_arg(pa, int);
		n = sc;
	}
	if (conv[1] == -1 || conv[2] < 0)
		return (ft_nbrm(n, ft_abs(conv[2]), conv[3], "0123456789"));
	else if (conv[3] != -1)
		return (ft_nbrp(n, conv[2], conv[3], "0123456789"));
	else
		return (ft_nbr0(n, conv[2], conv[1], "0123456789"));
}
