/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_unbr_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchemoun <jchemoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 16:29:00 by jchemoun          #+#    #+#             */
/*   Updated: 2019/11/15 13:45:09 by jchemoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <ft_printf.h>

int	ft_usnbr(unsigned long long int n, char *b)
{
	int				i;
	unsigned int	bl;

	bl = (int)ft_strlen(b);
	i = 0;
	while (n != 0)
	{
		n = n / bl;
		i++;
	}
	return (i);
}

int	ft_unbr0(unsigned long long int n, int field, int form, char *b)
{
	int		i;
	int		power;
	char	buf[field + 1];

	i = 0;
	power = ((n == 0) ? ft_usnbr(n, b) + 1 : ft_usnbr(n, b));
	while (i < field - power)
		buf[i++] = ((form == 0) ? '0' : ' ');
	return (write(1, buf, i) + ft_putnbr_base(n, b));
}

int	ft_unbrp(unsigned long long int n, int field, int prec, char *b)
{
	int		i;
	int		j;
	int		power;
	char	buf_s[field + 1];
	char	buf_0[ft_abs(prec)];

	i = 0;
	j = 0;
	power = ft_usnbr(n, b) ? ft_usnbr(n, b) : 1 - !prec;
	while (i < prec - power)
		buf_0[i++] = '0';
	while (j < field - (ft_max(prec, power)))
		buf_s[j++] = ' ';
	if (prec == 0 && n == 0)
		return (write(1, buf_s, j));
	else
		return (write(1, buf_s, j) + write(1, buf_0, i) + ft_putnbr_base(n, b));
}

int	ft_unbrm(unsigned long long int n, int field, int prec, char *b)
{
	int		i;
	int		j;
	int		power;
	char	buf_s[field];
	char	buf_0[ft_abs(prec)];

	i = 0;
	j = 0;
	power = ((n == 0) ? 1 - !prec : ft_usnbr(n, b));
	while (i < prec - power)
		buf_0[i++] = '0';
	while (j < field - (power + i))
		buf_s[j++] = ' ';
	if (prec != -1 && n == 0 && prec == 0)
		return (write(1, buf_s, j));
	else
		return (write(1, buf_0, i) + ft_putnbr_base(n, b) + write(1, buf_s, j));
}
