/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   into_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchemoun <jchemoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 10:49:47 by jchemoun          #+#    #+#             */
/*   Updated: 2021/04/03 14:10:08 by jchemoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_dupdup(int in, int out)
{
	dup2(in, 0);
	dup2(out, 1);
}

void	prep_pipe(int p1, int p2, int mode)
{
	close(p1);
	dup2(p2, mode);
	close(p2);
}

void	refork(int pipefd[2], char *rst, char ***envp)
{
	wait(0);
	prep_pipe(pipefd[1], pipefd[0], 0);
	if (!fork())
	{
		parse_line(rst, envp);
		exit(0);
	}
	else
		wait(0);
}

int	into_pipe(t_cmds cmds, char ***envp)
{
	int		pipefd[2];
	int		inout[2];
	pid_t	cpid;

	if (pipe(pipefd) == -1)
		return (ft_printf("Failure to pipe\n"));
	inout[0] = dup(0);
	inout[1] = dup(1);
	cpid = fork();
	if (cpid == -1)
		return (ft_printf("Failure to fork\n"));
	if (cpid == 0)
	{
		prep_pipe(pipefd[0], pipefd[1], 1);
		single_cmd(cmds, envp);
		exit(0);
	}
	else
		refork(pipefd, cmds.rst, envp);
	ft_dupdup(inout[0], inout[1]);
	free(cmds.rst);
	free_cmd(cmds);
	return (0);
}
