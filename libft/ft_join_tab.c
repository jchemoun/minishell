/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchemoun <jchemoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 10:56:35 by jchemoun          #+#    #+#             */
/*   Updated: 2021/04/03 14:54:03 by jchemoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	**ft_join_tabs(char **t1, char **t2)
{
	char	**re;
	size_t	i;
	size_t	j;
	size_t	len;

	i = 0;
	while (t1[i])
		i++;
	j = 0;
	while (t2[j])
		j++;
	re = malloc(sizeof(char *) * (i + j + 1));
	if (!re)
		return (0);
	len = 0;
	i = 0;
	j = 0;
	while (t1[i])
		re[len++] = ft_strdup(t1[i++]);
	while (t2[j])
		re[len++] = ft_strdup(t2[j++]);
	re[len] = 0;
	return (re);
}

char	**ft_join_tabs_free1(char **t1, char **t2)
{
	char	**re;

	re = ft_join_tabs(t1, t2);
	free_tab(t1);
	return (re);
}
