/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchemoun <jchemoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 12:37:36 by jchemoun          #+#    #+#             */
/*   Updated: 2019/11/05 16:52:26 by jchemoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	ft_atoi(const char *nptr)
{
	int i;
	int	re;
	int	signe;

	re = 0;
	signe = 1;
	i = 0;
	while (nptr[i] == ' ' || (nptr[i] > 8 && nptr[i] < 14))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		signe = 1 + (43 - nptr[i]);
		i++;
	}
	while (ft_isdigit(nptr[i]))
	{
		re = re * 10 + (signe * (nptr[i] - 48));
		i++;
	}
	return (re);
}
