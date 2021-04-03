/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchemoun <jchemoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 09:28:37 by jchemoun          #+#    #+#             */
/*   Updated: 2021/04/03 15:09:55 by jchemoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strrchr(const char *s, int c)
{
	char	*start;
	char	*cur;

	start = (char *)s;
	cur = start;
	while (*cur != '\0')
		cur++;
	while (cur >= start)
	{
		if (*cur == (char)c)
			return (cur);
		cur--;
	}
	return (0);
}
