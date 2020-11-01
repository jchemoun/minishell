/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   from_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchemoun <jchemoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 10:49:24 by jchemoun          #+#    #+#             */
/*   Updated: 2020/03/09 10:49:31 by jchemoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int		redir_form_file(t_cmds cmds, int fd, char ***envp)
{
	int		nstdin;

	nstdin = dup(0);
	dup2(fd, 0);
	if (cmds.sep > 2)
		ft_dispatch(cmds, envp);
	else
	{
		single_cmd(cmds, envp);
		cmds.cmd = malloc(1);
		cmds.cmd[0] = 0;
		cmds.args = malloc(sizeof(char*));
		cmds.args[0] = 0;
		ft_dispatch(cmds, envp);
	}
	close(fd);
	dup2(nstdin, 0);
	close(nstdin);
	return (0);
}

int		from_file(t_cmds cmds, char ***envp)
{
	size_t	i;
	int		fd;
	t_cmds	rst_cmd;

	i = 0;
	while (cmds.rst && ft_isspace(cmds.rst[i]))
		i++;
	if (cmds.rst == 0 || cmds.rst[i] == 0 || ft_isinset(cmds.rst[i], SEP_SET))
		return (ft_werror_token(cmds, cmds.rst[i], 2));
	rst_cmd.cmd = get_cmd(cmds.rst, &i);
	rst_cmd.args = get_args2(cmds.rst, &i);
	cmds.args = ft_join_tabs_free1(cmds.args, rst_cmd.args);
	if ((cmds.sep = get_sep(cmds.rst, &i)))
		rst_cmd.rst = ft_strdup(cmds.rst + i + 1 + (cmds.sep == 5));
	else
		rst_cmd.rst = 0;
	free(cmds.rst);
	cmds.rst = (cmds.sep) ? ft_strdup(rst_cmd.rst) : 0;
	free(rst_cmd.rst);
	if ((fd = open(rst_cmd.cmd, O_RDONLY)) == -1)
		return (ft_werror_file_from(envp, cmds, rst_cmd, 1));
	free_cmd(rst_cmd);
	return (redir_form_file(cmds, fd, envp));
}
