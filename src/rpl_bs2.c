/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rpl_bs2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchemoun <jchemoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 14:43:28 by user42            #+#    #+#             */
/*   Updated: 2021/04/19 10:31:37 by jchemoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	find_semicolon(char *line)
{
	int	i;
	int	inqu;
	int	indqu;

	i = 0;
	inqu = 0;
	indqu = 0;
	while (line[i])
	{
		if (line[i] == '\'' && !(indqu % 2) && (i == 0 || line[i - 1] != '\\'
				|| (i != 1 && line[i - 2] == '\\')))
			inqu += 1;
		if (line[i] == '\"' && !(inqu % 2) && (i == 0 || line[i - 1] != '\\'
				|| (i != 1 && line[i - 2] == '\\')))
			indqu += 1;
		if (line[i] == ';' && !(inqu % 2) && !(indqu % 2) && (i == 0
				|| line[i - 1] != '\\' || (i != 1 && line[i - 2] == '\\')))
		{
			return (i);
		}
		i++;
	}
	return (-1);
}

void	rpl_bs_inl(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == 1)
			line[i] = '\'';
		else if (line[i] == 2)
			line[i] = '"';
		else if (line[i] == 3)
			line[i] = '\\';
		else if (line[i] == 4)
			line[i] = '$';
		else if (line[i] == 5)
			line[i] = ';';
		else if (line[i] == 6)
			line[i] = '|';
		i++;
	}
}

void	rpl_bs_cmds(t_cmds cmds)
{
	int	i;

	i = 0;
	rpl_bs_inl(cmds.cmd);
	while (cmds.args[i])
	{
		rpl_bs_inl(cmds.args[i]);
		i++;
	}
}

void	rpl_bs_dquote2(char *line, char *nl, int j, int *k)
{
	nl[*k] = '\\';
	nl[*k + 1] = line[j + 1];
	*k = *k + 1;
}

int	rpl_bs_dquote(char *line, char *nl, int *j, int *k)
{
	int			i;
	static int	inqu = 0;
	static int	indqu = 0;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' && !(indqu % 2))
			inqu += 1;
		if (line[i] == '\"' && !(inqu % 2) && (i == 0 || line[i - 1] != '\\'
				|| (i != 1 && line[i - 2] == '\\')))
			indqu += 1;
		if (line[i] == '\\' && !(inqu % 2))
		{
			*j = *j + 1;
			if (indqu % 2 && nl)
				rpl_bs_dquote2(line, nl, i, k);
			else if (nl)
				nl[*k] = rpl_semicolon(line[i + 1]);
			return (42 / (1 + !(indqu % 2)));
		}
		i++;
	}
	reset_bs_dquote(nl, &inqu, &indqu);
	return (0);
}
