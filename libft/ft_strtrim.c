/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchemoun <jchemoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 10:23:19 by jchemoun          #+#    #+#             */
/*   Updated: 2019/11/05 16:53:05 by jchemoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static int	ft_found(const char str, const char *c)
{
	int i;

	i = 0;
	while (c[i] != '\0')
	{
		if (c[i] == str)
			return (1);
		i++;
	}
	return (0);
}

char		*ft_strtrim(const char *s1, const char *set)
{
	int len;

	if (!s1 || !set)
		return (NULL);
	while (s1 && ft_found(*s1, set))
		s1++;
	len = ft_strlen(s1) - 1;
	while (len > 0 && ft_found(s1[len], set))
		len--;
	if (s1 == '\0')
		return (ft_calloc(1, sizeof(char)));
	return (ft_substr(s1, 0, len + 1));
}
