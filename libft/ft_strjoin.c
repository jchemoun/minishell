/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchemoun <jchemoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 10:00:05 by jchemoun          #+#    #+#             */
/*   Updated: 2021/04/03 15:08:47 by jchemoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	size_t	i;
	size_t	j;
	char	*re;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (0);
	len = ft_strlen(s1) + ft_strlen(s2);
	re = malloc(len + 1);
	if (!re)
		return (0);
	while (s1 && s1[i])
	{
		re[i] = s1[i];
		i++;
	}
	while (s2 && s2[j])
	{
		re[i + j] = s2[j];
		j++;
	}
	re[i + j] = '\0';
	return (re);
}
