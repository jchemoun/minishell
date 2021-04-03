/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchemoun <jchemoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 11:07:02 by jchemoun          #+#    #+#             */
/*   Updated: 2021/04/03 13:38:39 by jchemoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_unset(t_cmds cmds, char ***envp)
{
	size_t	i;
	size_t	j;
	size_t	os;

	if (cmds.args[0] == 0)
		return (0);
	j = -1;
	while (cmds.args[++j])
	{
		i = -1;
		os = 0;
		while ((*envp)[++i + os])
		{
			if (cmds.args[j] && !ft_strncmp((*envp)[i + os], cmds.args[j],
				ft_charat((*envp)[i], '=')))
			{
				free((*envp)[i]);
				os++;
			}
			(*envp)[i] = (*envp)[i + os];
		}
		(*envp)[i] = 0;
	}
	free_cmd(cmds);
	return (0);
}
