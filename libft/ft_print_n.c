/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_n.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchemoun <jchemoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 16:36:59 by jchemoun          #+#    #+#             */
/*   Updated: 2019/11/05 17:18:13 by jchemoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <ft_printf.h>

static int	ft_print_nl(int flag, int re, va_list pa)
{
	void	*i;

	if (flag == 1)
	{
		i = va_arg(pa, long int*);
		*((long int*)i) = re;
	}
	else if (flag == 2)
	{
		i = va_arg(pa, long long int*);
		*((long long int*)i) = re;
	}
	return (0);
}

static int	ft_print_nh(int flag, int re, va_list pa)
{
	void *i;

	if (flag == -1)
	{
		i = va_arg(pa, long long int*);
		*((long long int*)i) = re;
	}
	else if (flag == -2)
	{
		i = va_arg(pa, signed char*);
		*((signed char*)i) = re;
	}
	return (0);
}

int			ft_print_n(int conv[N_FLAG], va_list pa)
{
	void	*i;

	if (conv[4] == 0)
	{
		i = va_arg(pa, int*);
		*((int*)i) = conv[5];
	}
	else if (conv[4] > 0)
		return (ft_print_nl(conv[4], conv[5], pa));
	else if (conv[4] < 0)
		return (ft_print_nh(conv[4], conv[5], pa));
	return (0);
}
