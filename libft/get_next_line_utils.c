/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchemoun <jchemoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 14:28:13 by jchemoun          #+#    #+#             */
/*   Updated: 2020/02/13 13:16:37 by jchemoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_init(int *found)
{
	char *re;

	*found = 0;
	if (!(re = malloc(1)))
		return (0);
	*re = 0;
	return (re);
}

int		ft_foundn(char *str, int size, int *found)
{
	int i;

	i = 0;
	while (i < size)
	{
		if (*(str + i) == '\n')
		{
			*found = 1;
			return (i);
		}
		i++;
	}
	return (i);
}

char	*ft_realloc(char *str, int len, int size)
{
	int		i;
	char	*new;

	i = 0;
	if (!(new = malloc(len + size + 1)))
		return (0);
	while (i < len)
	{
		*(new + i) = *(str + i);
		i++;
	}
	*(new + i) = 0;
	free(str);
	return (new);
}

void	ft_tabinit(int tab[5])
{
	int i;

	i = 0;
	while (i < 5)
	{
		tab[i] = 0;
		i++;
	}
}
