/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchemoun <jchemoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 15:46:35 by jchemoun          #+#    #+#             */
/*   Updated: 2021/04/03 14:53:14 by jchemoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static	int	power10(int p)
{
	int	re;

	re = 1;
	while (p > 0)
	{
		re = re * 10;
		p--;
	}
	return (re);
}

char	*ft_itoa(int n)
{
	int					i;
	int					power;
	unsigned int		temp;
	char				*re;

	i = n;
	power = 0;
	while (i != 0)
	{
		i = i / 10;
		power++;
	}
	re = malloc(sizeof(char) * (power + 2));
	if (!re)
		return (0);
	if (n < 0)
		re[i++] = '-';
	temp = ft_abs(n);
	if (n == 0)
		re[i++] = '0';
	while (power > 0)
		re[i++] = ((temp / power10(--power)) % 10) + 48;
	re[i] = '\0';
	return (re);
}
