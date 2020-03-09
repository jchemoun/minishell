/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchemoun <jchemoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 11:06:20 by jchemoun          #+#    #+#             */
/*   Updated: 2020/03/09 11:36:17 by jchemoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_exit(t_cmds cmds, char ***envp)
{
	int nb;
	int i;

	i = 0;
	if (cmds.args[0] == 0)
		exit(0);
	else if (cmds.args[1] != 0 && ft_isdigit(cmds.args[0][i]))
		return (ft_werrornoargfree("too many arguments", cmds, 1));
	if (cmds.args[0][i] == '+' || cmds.args[0][i] == '-')
		i++;
	while (ft_isdigit(cmds.args[0][i]))
		i++;
	if (cmds.args[0][i] != 0)
		return (ft_werrorfree("numeric argument required", cmds, 255));
	nb = ft_atoi(cmds.args[0]);
	exit((unsigned char)nb);
	(void)envp;
}
