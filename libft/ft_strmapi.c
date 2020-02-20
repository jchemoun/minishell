/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchemoun <jchemoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 16:39:24 by jchemoun          #+#    #+#             */
/*   Updated: 2019/11/05 16:53:05 by jchemoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int		i;
	size_t				len;
	char				*re;

	if (!s || !f)
		return (0);
	i = 0;
	len = ft_strlen(s);
	if (!(re = malloc(sizeof(char) * (len + 1))))
		return (0);
	while (i < len)
	{
		re[i] = (*f)(i, s[i]);
		i++;
	}
	re[i] = '\0';
	return (re);
}
