/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_werror.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchemoun <jchemoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 11:09:57 by jchemoun          #+#    #+#             */
/*   Updated: 2020/03/09 11:45:21 by jchemoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int		ft_werror(char *str, t_cmds cmds, int rcode)
{
	int	i;

	i = 0;
	ft_putstr_fd(cmds.cmd, 2);
	write(2, ": ", 2);
	while (cmds.args[i] && cmds.args[i][0] != 0)
	{
		ft_putstr_fd(cmds.args[i], 2);
		i++;
	}
	write(2, ": ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
	g_ret = rcode;
	return (1);
}

int		ft_werrornoarg(char *str, t_cmds cmds, int rcode)
{
	ft_putstr_fd(cmds.cmd, 2);
	write(2, ": ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
	g_ret = rcode;
	return (1);
}

int		ft_werror_file(char ***envp, t_cmds cmds, t_cmds rst_cmds, int rcode)
{
	if (!cmds.cmd || cmds.cmd[0] == 0)
		ft_putstr_fd("minishell: ", 2);
	else
		ft_putstr_fd(cmds.cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(rst_cmds.cmd, 2);
	ft_putstr_fd(": Permission denied", 2);
	ft_putstr_fd("\n", 2);
	free_cmd(rst_cmds);
	free(cmds.cmd);
	free_tab(cmds.args);
	cmds.cmd = malloc(1);
	cmds.cmd[0] = 0;
	cmds.args = malloc(sizeof(char*));
	cmds.args[0] = 0;
	if (cmds.sep < 3)
		ft_dispatch(cmds, envp);
	else
		free_cmd(cmds);
	g_ret = rcode;
	return (1);
}

int		ft_werror_file_from(char ***envp, t_cmds cmds,
								t_cmds rst_cmds, int rcode)
{
	g_ret = (cmds.sep == 1) ? rcode : g_ret;
	if (!cmds.cmd || cmds.cmd[0] == 0)
		ft_putstr_fd("minishell: ", 2);
	else
		ft_putstr_fd(cmds.cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(rst_cmds.cmd, 2);
	ft_putstr_fd(": No such file or directory", 2);
	ft_putstr_fd("\n", 2);
	free_cmd(rst_cmds);
	free(cmds.cmd);
	free_tab(cmds.args);
	cmds.cmd = malloc(1);
	cmds.cmd[0] = 0;
	cmds.args = malloc(sizeof(char*));
	cmds.args[0] = 0;
	if (cmds.sep < 3)
		ft_dispatch(cmds, envp);
	else
		free_cmd(cmds);
	g_ret = (cmds.sep != 1) ? rcode : g_ret;
	return (1);
}

int		ft_werror_token(t_cmds cmds, int token, int rcode)
{
	if (!cmds.cmd || cmds.cmd[0] == 0)
		ft_putstr_fd("minishell", 2);
	else
		ft_putstr_fd(cmds.cmd, 2);
	ft_putstr_fd(": syntax error near unexpected token ", 2);
	if (token == 0)
		ft_putstr_fd("`newline'", 2);
	else
	{
		ft_putchar_fd('`', 2);
		ft_putchar_fd((char)token, 2);
	}
	ft_putstr_fd("\'\n", 2);
	free(cmds.rst);
	free_cmd(cmds);
	g_ret = rcode;
	return (1);
}
