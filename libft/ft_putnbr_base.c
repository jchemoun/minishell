/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchemoun <jchemoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 16:19:28 by jchemoun          #+#    #+#             */
/*   Updated: 2019/11/15 13:25:38 by jchemoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	ft_putnbr_base(unsigned long long int n, char *base)
{
	unsigned int	len;
	unsigned int	re;

	len = (unsigned int)ft_strlen(base);
	re = 0;
	if (n < len)
		return (write(1, &base[n], 1));
	else
	{
		re += ft_putnbr_base(n / len, base);
		re += ft_putnbr_base(n % len, base);
	}
	return (re);
}
