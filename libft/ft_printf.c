/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchemoun <jchemoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 16:38:38 by jchemoun          #+#    #+#             */
/*   Updated: 2021/04/03 15:02:45 by jchemoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <ft_printf.h>

int	ft_print(int conv[N_FLAG], char typ, va_list pa, int *re)
{
	int	(*print_tab[N_CONV])(int conv[N_FLAG], va_list pa);
	int	i;

	i = 0;
	print_tab[0] = &ft_print_char;
	print_tab[1] = &ft_print_string;
	print_tab[2] = &ft_print_ptr;
	print_tab[3] = &ft_print_nbr;
	print_tab[4] = &ft_print_nbr;
	print_tab[5] = &ft_print_unbr;
	print_tab[6] = &ft_print_xnbr;
	print_tab[7] = &ft_print_mxnbr;
	print_tab[8] = &ft_print_pc;
	print_tab[9] = &ft_print_n;
	while (i < N_CONV)
	{
		if (CONVSET[i] == typ)
			return (*re += (*print_tab[i])(conv, pa));
		i++;
	}
	return (-1);
}

void	ft_tabinit_pf(int tab[N_FLAG], int *re)
{
	int	i;

	i = 0;
	while (i < N_FLAG)
	{
		tab[i] = 0;
		i++;
	}
	tab[1] = 2;
	tab[3] = -1;
	tab[4] = 0;
	tab[5] = *re;
}

int	ft_convert(const char *fi, int os, va_list pa, int *re)
{
	int conv[N_FLAG];

	ft_tabinit_pf(conv, re);
	while (fi[conv[0]] == '0' && conv[0] < os)
		conv[1] = 1 - !!(++conv[0]);
	while (fi[conv[0]] == '-' && conv[0] < os)
		conv[1] = -!!(++conv[0]);
	conv[2] = ft_atoi(fi + conv[0]);
	while (ft_isdigit(fi[conv[0]]))
		conv[0]++;
	if (fi[conv[0]] == '*' && conv[2] == 0 && ++conv[0])
		conv[2] = va_arg(pa, int);
	if (fi[conv[0]] == '.' && ++conv[0])
		conv[3] = (fi[conv[0]] == '*' && conv[0]++) ?
			va_arg(pa, int) : ft_atoi(fi + conv[0]);
	conv[3] < -1 ? conv[3] = -1 : 0;
	while (ft_isdigit(fi[conv[0]]))
		conv[0]++;
	while (fi[conv[0]] == 'l' && (conv[4] > 0 || conv[4] == 0))
		conv[4] += !!(++conv[0]);
	while (fi[conv[0]] == 'h' && (conv[4] < 0 || conv[4] == 0))
		conv[4] -= !!(++conv[0]);
	return (conv[0] == os ? ft_print(conv, fi[os], pa, re) : -1);
}

int	ft_ttribut(const char *f, size_t i, va_list pa, int *re)
{
	int	os;

	os = 0;
	while (ft_isinset(f[os + i], FLAGSET) || ft_isdigit(f[os + i]))
	{
		if (!f[os + i])
			return (-1);
		os++;
	}
	if (ft_isinset(f[os + i], CONVSET))
		ft_convert(f + i, os, pa, re);
	return (ft_isinset(f[os + i], CONVSET) ? os + 1 : os);
}

int	ft_printf(const char *f, ...)
{
	va_list	ap;
	size_t	i;
	int		re;
	int		os;

	va_start(ap, f);
	i = 0;
	re = 0;
	while (f[i])
	{
		os = 0;
		if (f[i] == '%')
		{
			if ((os = ft_ttribut(f, i + 1, ap, &re)) == -1)
				return (-1);
		}
		else
		{
			write(1, &f[i], 1);
			re++;
		}
		i = os + i + 1;
	}
	va_end(ap);
	return (re);
}
