/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchemoun <jchemoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 10:56:35 by jchemoun          #+#    #+#             */
/*   Updated: 2021/04/03 15:17:57 by jchemoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	**push_front_tab(char *cp, char **args)
{
	char	**re;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (args[i])
		i++;
	re = malloc(sizeof(char *) * (i + 2));
	if (!re)
		return (0);
	re[0] = ft_strdup(cp);
	while (j < i)
	{
		re[j + 1] = ft_strdup(args[j]);
		j++;
	}
	re[j + 1] = 0;
	return (re);
}

char	**push_front_tab_free(char *cp, char **args)
{
	char	**re;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (args[i])
		i++;
	re = malloc(sizeof(char *) * (i + 2));
	if (!re)
		return (0);
	re[0] = ft_strdup(cp);
	while (j < i)
	{
		re[j + 1] = ft_strdup(args[j]);
		j++;
	}
	re[j + 1] = 0;
	free_tab(args);
	return (re);
}

char	**push_back_tab_free(char *cp, char **args)
{
	char	**re;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (args[i])
		i++;
	re = malloc(sizeof(char *) * (i + 2));
	if (!re)
		return (0);
	while (j < i)
	{
		re[j] = ft_strdup(args[j]);
		j++;
	}
	re[j] = ft_strdup(cp);
	re[j + 1] = 0;
	free_tab(args);
	return (re);
}

char	**push_front_tab_free2(char *cp, char **args)
{
	char	**re;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (args[i])
		i++;
	re = malloc(sizeof(char *) * (i + 2));
	if (!re)
		return (0);
	re[0] = ft_strdup(cp);
	while (j < i)
	{
		re[j + 1] = ft_strdup(args[j]);
		j++;
	}
	re[j + 1] = 0;
	free_tab(args);
	free(cp);
	return (re);
}

int	free_tab(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args[i]);
	free(args);
	return (1);
}
