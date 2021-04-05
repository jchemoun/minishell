/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rpl_bs2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchemoun <jchemoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 14:43:28 by user42            #+#    #+#             */
/*   Updated: 2021/04/05 13:57:02 by jchemoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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

void	rpl_bs_dquote2(char *line, char *nl, int *j, int *k)
{
	nl[*k] = '\\';
	nl[*k + 1] = line[*j + 1];
	*j = *j + 1;
	*k = *k + 1;
}

void	rpl_bs_dquote(char *line, char *nl, int *j, int *k)
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
		{
			if (indqu % 2)
				rpl_bs_dquote2(line, nl, j, k);
			else
				nl[*k] = line[*j + 1];
		}
		i++;
	}
}
