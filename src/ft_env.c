/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchemoun <jchemoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 11:06:39 by jchemoun          #+#    #+#             */
/*   Updated: 2020/03/09 11:06:45 by jchemoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int		ft_env(t_cmds cmds, char ***envp)
{
	size_t	i;

	i = 0;
	free_cmd(cmds);
	while ((*envp)[i])
	{
		ft_printf("%s\n", (*envp)[i]);
		i++;
	}
	return (0);
}
