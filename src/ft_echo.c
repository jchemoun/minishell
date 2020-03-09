/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchemoun <jchemoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 11:05:07 by jchemoun          #+#    #+#             */
/*   Updated: 2020/03/09 11:05:20 by jchemoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int		ft_echo(t_cmds cmds, char ***envp)
{
	int	i;
	int	nl;

	i = 0;
	if (cmds.args[0])
		nl = 1 - !!(ft_strncmp("-n", cmds.args[i], 3));
	else
		nl = 0;
	while (cmds.args[i + nl])
	{
		ft_printf("%s", cmds.args[i + nl]);
		i++;
		if (cmds.args[i + nl])
			ft_printf(" ");
	}
	if (!nl)
		ft_printf("\n");
	free_cmd(cmds);
	(void)envp;
	return (0);
}
