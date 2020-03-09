/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchemoun <jchemoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 17:16:45 by jchemoun          #+#    #+#             */
/*   Updated: 2020/03/09 12:02:37 by jchemoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char		*read_line(void)
{
	char	*buf;
	int		c;

	c = 2;
	buf = 0;
	while (c)
	{
		ft_printf("> ");
		c = get_next_line_cd(0, &buf);
		if (c == 1)
			return (buf);
		else if (c == 0 && *buf == 0)
		{
			ft_printf("exit\n");
			exit(0);
		}
	}
	return (0);
}

void	ft_dispatch(t_cmds cmds, char ***envp)
{
	int	i;
	int	old_ret;

	i = 0;
	old_ret = g_ret;
	if (check_err(cmds))
		return ;
	if (cmds.sep == 0 || cmds.sep == 1)
		i = single_cmd(cmds, envp);
	if (cmds.sep == 2)
		i = into_pipe(cmds, envp);
	if (cmds.sep == 3)
		i = from_file(cmds, envp);
	if (cmds.sep == 4 || cmds.sep == 5)
		i = into_file(cmds, envp, cmds.sep - 4);
	if (i == 0)
		g_ret = 0;
}

void	entry_loop(char ***envp)
{
	char	*line;
	int		stop;
	//pid_t	pid;

	stop = 0;
	//if ((pid = fork()) < 0)
	//{
	//	ft_printf("Fork_Error\n");
	//	exit(1);
	//}
	//else if (pid > 0)
	//{
	//	//signal(2, signal_callback_handler);
	//	waitpid(pid, NULL, 0);
	//}
	//else
	//{
	while (!stop)
	{
		signal(SIGINT, signal_callback_handler);
		signal(3, sign3);
		line = read_line();
		//parse_input(line, envp);
		//printf("%s\n", get_var_env(line, envp));
		get_var_env(&line, 0, *envp);
		//printf("POSTVAR :%s\n", line);
		stop = parse_line(line, envp);
		//printf("%s\n", line);
		//system("leaks minishell");
	}
	//}
}

int	main(int argc, char **argv, char **envp)
{
	char **nenvp;
	struct stat susless;

	signal(SIGINT, signal_callback_handler);
	signal(3, sign3);
	nenvp = ft_copy(envp);
	stat(argv[0], &susless);
	get_perm(susless, 1);
	g_ret = 0;
	entry_loop(&nenvp);
	//system("leaks a.out");
	return (0);
	(void)argc;
}
