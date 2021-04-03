/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchemoun <jchemoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 12:56:27 by jchemoun          #+#    #+#             */
/*   Updated: 2021/04/03 14:50:53 by jchemoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	*ft_calloc(size_t count, size_t size)
{
	void	*re;

	if (!count || !size)
	{
		count = 1;
		size = 1;
	}
	re = malloc(count * size);
	if (!re)
		return (0);
	ft_bzero(re, count * size);
	return (re);
}
