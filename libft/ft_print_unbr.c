/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_unbr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchemoun <jchemoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 16:27:08 by jchemoun          #+#    #+#             */
/*   Updated: 2019/11/05 17:08:26 by jchemoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <ft_printf.h>

int	ft_print_ptr(int conv[N_FLAG], va_list pa)
{
	unsigned long int	n;
	int					i;
	int					power;
	int					field;
	char				buf[ft_abs(conv[2])];

	n = (unsigned long int)va_arg(pa, void*);
	field = ft_abs(conv[2]);
	i = 0;
	power = (ft_usnbr(n, "0123456789abcdef") > 0) ?
			ft_usnbr(n, "0123456789abcdef") :
			ft_usnbr(n, "0123456789abcdef") + 1;
	while (i < field - power - 2)
		buf[i++] = ' ';
	if (conv[1] == -1 || conv[2] < 0)
		return (write(1, "0x", 2) +
			ft_putnbr_base(n, "0123456789abcdef") + write(1, buf, i));
	else
		return (write(1, buf, i) + write(1, "0x", 2) +
			ft_putnbr_base(n, "0123456789abcdef"));
}

int	ft_print_mxnbr(int conv[N_FLAG], va_list pa)
{
	unsigned long long int	n;
	unsigned char			uc;

	if (conv[4] == 0)
		n = va_arg(pa, unsigned int);
	else if (conv[4] == 1)
		n = va_arg(pa, unsigned long int);
	else if (conv[4] == 2)
		n = va_arg(pa, unsigned long long int);
	else if (conv[4] == -1)
		n = (unsigned short)va_arg(pa, unsigned int);
	else if (conv[4] == -2)
	{
		uc = (unsigned char)va_arg(pa, unsigned int);
		n = uc;
	}
	if (conv[1] == -1 || conv[2] < 0)
		return (ft_unbrm(n, ft_abs(conv[2]), conv[3], "0123456789ABCDEF"));
	else if (conv[3] != -1)
		return (ft_unbrp(n, conv[2], conv[3], "0123456789ABCDEF"));
	else
		return (ft_unbr0(n, conv[2], conv[1], "0123456789ABCDEF"));
}

int	ft_print_xnbr(int conv[N_FLAG], va_list pa)
{
	unsigned long long int	n;
	unsigned char			uc;

	if (conv[4] == 0)
		n = va_arg(pa, unsigned int);
	else if (conv[4] == 1)
		n = va_arg(pa, unsigned long int);
	else if (conv[4] == 2)
		n = va_arg(pa, unsigned long long int);
	else if (conv[4] == -1)
		n = (unsigned short)va_arg(pa, unsigned int);
	else if (conv[4] == -2)
	{
		uc = (unsigned char)va_arg(pa, unsigned int);
		n = uc;
	}
	if (conv[1] == -1 || conv[2] < 0)
		return (ft_unbrm(n, ft_abs(conv[2]), conv[3], "0123456789abcdef"));
	else if (conv[3] != -1)
		return (ft_unbrp(n, conv[2], conv[3], "0123456789abcdef"));
	else
		return (ft_unbr0(n, conv[2], conv[1], "0123456789abcdef"));
}

int	ft_print_unbr(int conv[N_FLAG], va_list pa)
{
	unsigned long long int	n;
	unsigned char			uc;

	if (conv[4] == 0)
		n = va_arg(pa, unsigned int);
	else if (conv[4] == 1)
		n = va_arg(pa, unsigned long int);
	else if (conv[4] == 2)
		n = va_arg(pa, unsigned long long int);
	else if (conv[4] == -1)
		n = (unsigned short)va_arg(pa, unsigned int);
	else if (conv[4] == -2)
	{
		uc = (unsigned char)va_arg(pa, unsigned int);
		n = uc;
	}
	if (conv[1] == -1 || conv[2] < 0)
		return (ft_unbrm(n, ft_abs(conv[2]), conv[3], "0123456789"));
	else if (conv[3] != -1)
		return (ft_unbrp(n, conv[2], conv[3], "0123456789"));
	else
		return (ft_unbr0(n, conv[2], conv[1], "0123456789"));
}
