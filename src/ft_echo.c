/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchemoun <jchemoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 11:05:07 by jchemoun          #+#    #+#             */
/*   Updated: 2021/04/03 13:27:39 by jchemoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_opt_n(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] != '-')
		return (0);
	i++;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	ft_echo(t_cmds cmds, char ***envp)
{
	int	i;
	int	nl;

	i = 0;
	nl = 0;
	while (cmds.args[nl] && (is_opt_n(cmds.args[nl])))
		nl++;
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
