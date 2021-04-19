/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rpl_bs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchemoun <jchemoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 12:39:05 by user42            #+#    #+#             */
/*   Updated: 2021/04/19 10:24:19 by jchemoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	find_bs(char *line)
{
	int	i;
	int	inqu;
	int	indqu;

	i = 0;
	inqu = 0;
	indqu = 0;
	while (line[i])
	{
		if (line[i] == '\'' && !(indqu % 2))
			inqu += 1;
		if (line[i] == '\"' && !(inqu % 2))
			indqu += 1;
		if (line[i] == '\\' && !(inqu % 2))
			return (i);
		i++;
	}
	return (-1);
}

int	which_bs(char c, char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (i + 1);
		i++;
	}
	return (0);
}

void	fill_rst(char *line, char *nl)
{
	int	i;

	i = 0;
	while (line[i])
	{
		nl[i] = line[i];
		i++;
	}
	nl[i] = '\0';
	rpl_bs_dquote(line, 0, &i, &i);
}

void	recu_bs(char *line, char *nl, int *i)
{
	int	j;
	int	bs;

	j = 0;
	while (j < *i)
	{
		nl[j] = line[j];
		j++;
	}
	bs = which_bs((line)[*i + 1], "'\"\\$");
	if (bs)
	{
		nl[j] = bs;
		*i = *i + 1;
	}
	else
		bs = rpl_bs_dquote(line, nl, i, &j);
	*i = find_bs((line + *i + 1));
	if (*i == -1)
		fill_rst(line + j + 1 + (bs != 42), (nl + j + 1));
	else
		recu_bs(line + j + 1 + (bs != 42), nl + j + 1, i);
}

void	rpl_bs_ligne(char **line)
{
	int		i;
	char	*nl;

	i = find_bs(*line);
	nl = malloc(ft_strlen(*line) + 1);
	if (i != -1)
		recu_bs(*line, nl, &i);
	else
		fill_rst(*line, nl);
	free(*line);
	*line = nl;
}
