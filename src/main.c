/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchemoun <jchemoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 17:16:45 by jchemoun          #+#    #+#             */
/*   Updated: 2021/04/03 12:41:36 by jchemoun         ###   ########.fr       */
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
			write(0, "exit\n", 5);
			exit(0);
		}
	}
	return (0);
}

void		ft_dispatch(t_cmds cmds, char ***envp)
{
	int	i;

	i = 0;
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

void		entry_loop(char ***envp)
{
	char			*line;
	int				stop;
	t_historia_dc	*historia;

	stop = 0;
	historia = malloc(sizeof(t_historia_dc));
	if (!historia)
		proper_exit(1, 1);
	historia->prev = 0;
	historia->next = 0;
	historia->str = 0;
	while (!stop)
	{
		signal(SIGINT, signal_callback_handler);
		signal(3, sign3);
		line = read_linev2(&historia);
		add_historia(line, &historia);
		stop = parse_line(line, envp);
	}
}

int			main(int argc, char **argv, char **envp)
{
	char		**nenvp;
	struct stat	susless;

	signal(SIGINT, signal_callback_handler);
	signal(3, sign3);
	if (!envp[0])
		nenvp = ft_base_env();
	else
		nenvp = ft_copy(envp);
	stat(argv[0], &susless);
	get_perm(susless, 1);
	g_ret = 0;
	enable_rawmode();
	entry_loop(&nenvp);
	return (0);
	(void)argc;
}
