/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchemoun <jchemoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 10:56:35 by jchemoun          #+#    #+#             */
/*   Updated: 2020/03/09 11:48:44 by jchemoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char		**push_front_tab(char *cp, char **args)
{
	char	**re;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (args[i])
		i++;
	if (!(re = malloc(sizeof(char*) * (i + 2))))
		return (0);
	re[0] = strdup(cp);
	while (j < i)
	{
		re[j + 1] = strdup(args[j]);
		j++;
	}
	re[j + 1] = 0;
	return (re);
}

char		**push_front_tab_free(char *cp, char **args)
{
	char	**re;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (args[i])
		i++;
	if (!(re = malloc(sizeof(char*) * (i + 2))))
		return (0);
	re[0] = strdup(cp);
	while (j < i)
	{
		re[j + 1] = strdup(args[j]);
		j++;
	}
	re[j + 1] = 0;
	free_tab(args);
	return (re);
}

char		**push_back_tab_free(char *cp, char **args)
{
	char	**re;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (args[i])
		i++;
	if (!(re = malloc(sizeof(char*) * (i + 2))))
		return (0);
	while (j < i)
	{
		re[j] = strdup(args[j]);
		j++;
	}
	re[j] = strdup(cp);
	re[j + 1] = 0;
	free_tab(args);
	return (re);
}

char		**ft_join_tabs(char **t1, char **t2)
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
	if (!(re = malloc(sizeof(char*) * (i + j + 1))))
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

char		**ft_join_tabs_free1(char **t1, char **t2)
{
	char	**re;

	re = ft_join_tabs(t1, t2);
	free_tab(t1);
	return (re);
}
