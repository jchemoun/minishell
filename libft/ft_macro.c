/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_macro.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchemoun <jchemoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 16:17:27 by jchemoun          #+#    #+#             */
/*   Updated: 2019/11/22 10:08:53 by jchemoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

unsigned int	ft_abs(int x)
{
	return ((x < 0) ? -x : x);
}

int				ft_min(int a, int b)
{
	return ((((a) < (b)) ? (a) : (b)));
}

int				ft_max(int a, int b)
{
	return ((((a) > (b)) ? (a) : (b)));
}
