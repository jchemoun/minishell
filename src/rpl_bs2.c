/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rpl_bs2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 14:43:28 by user42            #+#    #+#             */
/*   Updated: 2020/11/02 15:09:00 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	rpl_bs_inl(char *line)
{
	int i;

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
	int i;

	i = 0;
	rpl_bs_inl(cmds.cmd);
	while (cmds.args[i])
	{
		rpl_bs_inl(cmds.args[i]);
		i++;
	}
}
