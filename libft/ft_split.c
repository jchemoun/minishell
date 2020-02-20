/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchemoun <jchemoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 14:11:43 by jchemoun          #+#    #+#             */
/*   Updated: 2019/11/05 16:53:05 by jchemoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static int		ft_strndlen(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static int		ft_countw(char const *s, char c)
{
	size_t	i;
	int		re;
	char	prev;

	i = 0;
	re = 0;
	prev = s[0];
	while (s[i])
	{
		if ((s[i] != c && prev == c) || (s[i] != c && i == 0))
			re++;
		prev = s[i];
		i++;
	}
	return (re);
}

static	char	*ft_strdnup(char const *s, int c)
{
	int		i;
	int		len;
	char	*re;

	i = 0;
	len = ft_strndlen(s, c);
	if (!(re = malloc(len + 1)))
		return (0);
	while (i < len)
	{
		re[i] = s[i];
		i++;
	}
	re[i] = '\0';
	return (re);
}

char			**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	int		n_word;
	char	prev;
	char	**re;

	if (!s)
		return (0);
	i = 0;
	j = 0;
	n_word = ft_countw(s, c);
	prev = s[0];
	if (!(re = malloc(sizeof(char*) * (n_word + 1))))
		return (0);
	while (s[i] && j < n_word)
	{
		if ((s[i] != c && prev == c) || (s[i] != c && i == 0))
			re[j++] = ft_strdnup(s + i, c);
		prev = s[i];
		i++;
	}
	re[j] = 0;
	return (re);
}
