/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchemoun <jchemoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 10:52:16 by jchemoun          #+#    #+#             */
/*   Updated: 2021/04/19 10:42:01 by jchemoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	simple_exec(t_cmds cmds, char **envp, char *cp)
{
	char	**argv;
	int		status;

	argv = push_front_tab(cp, cmds.args);
	if (!fork())
	{
		disable_rawmode();
		execve(cp, argv, envp);
		exit(0);
	}
	else
	{
		signal(2, global_change);
		signal(3, global_change);
		wait(&status);
	}
	enable_rawmode();
	if (cmds.cmd != cp)
		free(cp);
	free_tab(argv);
	free_cmd(cmds);
	tern_g_code(status);
	return (W_EXITCODE(WEXITSTATUS(status), status));
}

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (!ft_strncmp("echo", cmd, 5))
		return (1);
	if (!ft_strncmp("cd", cmd, 3))
		return (2);
	if (!ft_strncmp("pwd", cmd, 4))
		return (3);
	if (!ft_strncmp("export", cmd, 7))
		return (4);
	if (!ft_strncmp("unset", cmd, 6))
		return (5);
	if (!ft_strncmp("env", cmd, 4))
		return (6);
	if (!ft_strncmp("exit", cmd, 5))
		return (7);
	if (!ft_strncmp("", cmd, 1))
		return (8);
	return (0);
}

int	single_cmd(t_cmds cmds, char ***envp)
{
	int		i;
	int		ret;
	char	*cp;
	int		(*builtin[8])(t_cmds cmds, char ***envp);

	init_builtin(&builtin);
	ret = 0;
	i = is_builtin(cmds.cmd);
	cp = 0;
	if (i)
	{
		ret = builtin[i - 1](cmds, envp);
		i = -1;
	}
	else
		cp = isinpath(cmds, *envp, &i);
	if (i != -1 && cp)
		ret = simple_exec(cmds, *envp, cp);
	else if (i != -1 && cp == 0 && isindir(cmds, &i, &ret))
		ret = simple_exec(cmds, *envp, cmds.cmd);
	else if (i != -1)
		ret = cmd_not_f(cmds);
	if (cmds.sep == 1)
		parse_line(cmds.rst, envp);
	return (ret);
}
