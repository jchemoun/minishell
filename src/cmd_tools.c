/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchemoun <jchemoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 12:44:28 by jchemoun          #+#    #+#             */
/*   Updated: 2021/04/05 12:45:01 by jchemoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_empty_cmd(t_cmds cmds, char ***envp)
{
	(void)envp;
	free_cmd(cmds);
	return (0);
}

int	cmd_not_f(t_cmds cmds)
{
	ft_werror("command not found", cmds, 127);
	free_cmd(cmds);
	return (1);
}

void	init_builtin(int (*(*builtin)[8])(t_cmds, char ***envp))
{
	(*builtin)[0] = &ft_echo;
	(*builtin)[1] = &ft_cd;
	(*builtin)[2] = &ft_pwd;
	(*builtin)[3] = &ft_export;
	(*builtin)[4] = &ft_unset;
	(*builtin)[5] = &ft_env;
	(*builtin)[6] = &ft_exit;
	(*builtin)[7] = &ft_empty_cmd;
}
