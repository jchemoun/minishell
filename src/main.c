/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchemoun <jchemoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 17:16:45 by jchemoun          #+#    #+#             */
/*   Updated: 2020/03/03 15:31:10 by jchemoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int			ft_isspace(char c)
{
	if (c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r' || c == ' ')
		return (1);
	return (0);
}

size_t		ft_charat(const char *str, int c)
{
	size_t i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

void		signal_callback_handler(int signum)
{
	ft_printf("\n> ");
}

void		sign3(int signum)
{
	return ;
}

int			free_tab(char **args)
{
	int i;

	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args[i]);
	free(args);
	return (1);
}

void		free_cmd(t_cmds cmds)
{
	free(cmds.cmd);
	free_tab(cmds.args);
}

char		*ft_strjoinfree2(const char *s1, const char *s2)
{
	size_t	len;
	size_t	i;
	size_t	j;
	char	*re;

	i = 0;
	j = 0;
	len = ft_strlen(s1) + ft_strlen(s2);
	if (!(re = malloc(len + 1)))
		return (0);
	while (s1 && s1[i])
	{
		re[i] = s1[i];
		i++;
	}
	while (s2 && s2[j])
	{
		re[i + j] = s2[j];
		j++;
	}
	re[i + j] = '\0';
	free((void*)s2);
	return (re);
}

char		**push_front_tab(char *cp, char **args)
{
	char	**re;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (args[i])
		i++;
	if (!(re = malloc(sizeof(char*) * (i + 2))))
		return (0);
	re[0] = strdup(cp);
	while (j < i)
	{
		re[j + 1] = strdup(args[j]);
		j++;
	}
	re[j + 1] = 0;
	return (re);
}

char		**push_front_tab_free(char *cp, char **args)
{
	char	**re;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (args[i])
		i++;
	if (!(re = malloc(sizeof(char*) * (i + 2))))
		return (0);
	re[0] = strdup(cp);
	while (j < i)
	{
		re[j + 1] = strdup(args[j]);
		j++;
	}
	re[j + 1] = 0;
	free_tab(args);
	return (re);
}

char		**ft_join_tabs(char **t1, char **t2)
{
	char	**re;
	size_t	i;
	size_t	j;
	size_t len;

	i = 0;
	while (t1[i])
		i++;
	j = 0;
	while (t2[j])
		j++;
	if (!(re = malloc(sizeof(char*) * (i + j + 1))))
		return (0);
	len = 0;
	i = 0;
	j = 0;
	while (t1[i])
		re[len++] = ft_strdup(t1[i++]);
	while (t2[j])
		re[len++] = ft_strdup(t2[j++]);
	re[len] = 0;
	return (re);

}

char		**ft_join_tabs_free1(char **t1, char **t2)
{
	char	**re;

	re = ft_join_tabs(t1, t2);
	free_tab(t1);
	return (re);
}

int			ft_nbl(char **envp)
{
	int i;

	i = 0;
	while(envp[i])
		i++;
	return (i);
}

char	**ft_copy(char **envp)
{
	char **fenv;
	int i;

	if (!(fenv = malloc(sizeof(char *) * (ft_nbl(envp) + 1))))
		return (NULL);
	i = 0;
	while(envp[i])
	{
		fenv[i] = ft_strdup(envp[i]);
		i++;
	}
	fenv[i] = 0;
	return (fenv);	
}

char		**ft_sort_env(char **fenv)
{
	int i;
	char *tmp;

	i = 0;
	while(fenv[i + 1])
	{
		if (ft_strncmp(fenv[i], fenv[i + 1], ft_charat(fenv[i], '=') >
			ft_charat(fenv[i + 1], '=') ? ft_charat(fenv[i], '=') :
			ft_charat(fenv[i + 1], '=')) > 0)
		{
			tmp = fenv[i];
			fenv[i] = fenv[i + 1];
			fenv[i + 1] = tmp;
			i = 0;
		}
		else
			i++;
	}
	return(fenv);
}

void		ft_displayfree(char **fenv)
{
	int i;
	i = 0;
	while(fenv[i])
	{
		ft_printf("%s\n", fenv[i]);
		i++;
	}
	free_tab(fenv);
}

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

void		ft_echo(t_cmds cmds, char ***envp)
{
	int i;
	int nl;

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
}

void		ft_cd(t_cmds cmds, char ***envp)
{
	struct stat buf;

	if (stat(cmds.args[0], &buf) == -1)
	{
		ft_printf("no such file or directory: %s\n", cmds.cmd);
		free_cmd(cmds);
		return ;
	}
	if (get_perm(buf, 0))
	{
		chdir(cmds.args[0]);
		free_cmd(cmds);
	}
	else
	{
		ft_printf("permission denied: %s\n", cmds.cmd);
		free_cmd(cmds);
	}
}

void		ft_pwd(t_cmds cmds, char ***envp)
{
	char pwd[BUF_S];

	free_cmd(cmds);
	if (!(getcwd(pwd, BUF_S)))
	{
		ft_printf("Error in getcwd\n");
		return ;
	}
	ft_printf("%s\n", pwd);
}

void		ft_export(t_cmds cmds, char ***envp)
{
	size_t	i;
	size_t	j;

	j = 0;
	if (cmds.args[0] == 0)
	{
		ft_displayfree(ft_sort_env(ft_copy(*envp)));
		return ;
	}
	while (cmds.args[j])
	{
		if (ft_charat(cmds.args[j], '=') != (size_t)-1)
		{
			i = 0;
			while ((*envp)[i] && ft_strncmp((*envp)[i], cmds.args[j], ft_charat((*envp)[i], '=')))
				i++;
			if ((*envp)[i] != 0)
				(*envp)[i] = cmds.args[j];
			else
				(*envp) = push_front_tab(cmds.args[j], (*envp));
		}
		j++;
	}
	free_cmd(cmds);
}

void		ft_unset(t_cmds cmds, char ***envp)
{
	size_t	i;
	size_t	j;
	size_t	os;

	if (cmds.args[0] == 0)
		return ;
	j = 0;
	while (cmds.args[j])
	{
		i = 0;
		os = 0;
		while ((*envp)[i + os])
		{
			if (cmds.args[j] && !ft_strncmp((*envp)[i + os], cmds.args[j], ft_charat((*envp)[i], '=')))
				os++;
			(*envp)[i] = (*envp)[i + os];
			i++;
		}
		(*envp)[i] = 0;
		j++;
	}
	free_cmd(cmds);
}

void		ft_env(t_cmds cmds, char ***envp)
{
	size_t	i;

	i = 0;
	free_cmd(cmds);
	while ((*envp)[i])
	{
		ft_printf("%s\n", (*envp)[i]);
		i++;
	}
}

void	ft_exit(t_cmds cmds, char ***envp)
{
	int nb;
	int i;

	i = 0;
	if (cmds.args[0] == 0)
		exit(0);
	else if (cmds.args[1] != 0)
	{
		ft_printf("Too many argument\n");
		return ;
	}
	if (cmds.args[0][i] == '+' || cmds.args[0][i] == '-')
		i++;
	while(ft_isdigit(cmds.args[0][i]))
		i++;
	if (cmds.args[0][i] != 0)
	{
		ft_printf("Numeric argument required\n");
		return ;
	}
	nb = ft_atoi(cmds.args[0]);
	exit((unsigned char)nb);
}

void		ft_empty_cmd(t_cmds cmds, char ***envp)
{
	free_cmd(cmds);
	return ;
}

/*
char	*fi_quote(char *line, int fquote)
{
	char	*nl;
	int		i;
	int		c;

	c = 1;
	while (c)
	{
		c = get_next_line(0, &nl);
		i = 0;
		while (nl[i])
		{
			if (nl[i] == ((fquote == 1) ? '\'' : '\"'))
				c = 0;
			i++;
		}
	}
	return (ft_strjoin_free(line, nl));
}

char	*check_quote2(char *line)
{
	int		i;
	int		inqu;
	int		indqu;
	int		fquote;

	i = 0;
	inqu = 0;
	indqu = 0;
	fquote = 0;
	while (line[i])
	{
		if (line[i] == '\'')
			inqu += 1;
		if (line[i] == '\"')
			indqu += 1;
		if (inqu % 2 && !(indqu % 2))
			fquote = -1;
		if (indqu % 2 && !(inqu % 2))
			fquote = 1;
		i++;
	}
	if (inqu % 2 || indqu % 2)
		return (fi_quote(line, fquote));
	return (line);
}*/

int		check_err(t_cmds cmds)
{
	if (cmds.sep > 1 && cmds.rst == 0)
	{
		ft_printf("parse error near `\\n'");
		free_cmd(cmds);
		return (1);
	}
	return (0);
}

void	cmd_not_f(t_cmds cmds)
{
	ft_printf("command not found: %s\n", cmds.cmd);
	free_cmd(cmds);
}

int		is_builtin(char *cmd)
{
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

char	*get_path(char **envp)
{
	int	j;

	j = 0;
	while (envp[j] && ft_strncmp(envp[j], "PATH", ft_charat(envp[j], '=')))
		j++;
	return (envp[j]);
}

void	simple_exec(t_cmds cmds, char **envp, char *cp)
{
	char **argv;

	argv = push_front_tab(cp, cmds.args);
	if (!fork())
	{
		execve(cp, argv, envp);
		exit(0);
	}
	else
		wait(0);
	if (cmds.cmd != cp)
		free(cp);
	free_tab(argv);
	free_cmd(cmds);
	return ;
}

int		get_perm(struct stat buf, int f)
{
	static struct stat min;

	if (f)
	{
		stat("./minishell", &min);
		return (1);
	}
	if (buf.st_uid == min.st_uid && buf.st_mode & 00100)
		return (1);
	if (buf.st_uid != min.st_uid &&
		buf.st_gid == min.st_gid && buf.st_mode & 00010)
		return (1);
	if (buf.st_uid != min.st_uid &&
		buf.st_gid != min.st_gid && buf.st_mode & 00001)
		return (1);
	return (0);
}

char	*isinpath(t_cmds cmds, char **envp, int *j)
{
	struct stat	buf;
	char		**paths;
	char		*nl;
	int			i;

	if (!(paths = ft_split(get_path(envp), ':')))
		return (0);
	i = 0;
	while (paths[i])
	{
		if (stat(nl = ft_strjoinfree2(paths[i],
			ft_strjoin("/", cmds.cmd)), &buf) == -1)
			free(nl);
		else
			break ;
		nl = 0;
		i++;
	}
	free_tab(paths);
	if (get_perm(buf, 0))
		return (nl);
	else if (nl != 0)
		*j = 0 - !!ft_printf("permission denied: %s\n", cmds.cmd);
	return (0);
}

int		isindir(t_cmds cmds, char **envp, int *j)
{
	int i;
	struct stat buf;

	if ((i = ft_charat(cmds.cmd, '/')) == -1)
		return (0);
	if (stat(cmds.cmd, &buf) == -1)
	{
		*j = -1;
		ft_printf("no such file or directory: %s\n", cmds.cmd);
		free_cmd(cmds);
		return (0);
	}
	if (get_perm(buf, 0))
		return (1);
	else
	{
		*j = -1;
		ft_printf("permission denied: %s\n", cmds.cmd);
		free_cmd(cmds);
	}
	return (0);
}

void	single_cmd(t_cmds cmds, char ***envp)
{
	int		i;
	char	*cp;
	void	(*builtin[8])(t_cmds cmds, char ***envp);

	builtin[0] = &ft_echo;
	builtin[1] = &ft_cd;
	builtin[2] = &ft_pwd;
	builtin[3] = &ft_export;
	builtin[4] = &ft_unset;
	builtin[5] = &ft_env;
	builtin[6] = &ft_exit;
	builtin[7] = &ft_empty_cmd;
	if ((i = is_builtin(cmds.cmd)))
		builtin[i - 1](cmds, envp);
	else if ((cp = isinpath(cmds, *envp, &i)))
		simple_exec(cmds, *envp, cp);
	else if (i != -1 && cp == 0 && isindir(cmds, *envp, &i))
		simple_exec(cmds, *envp, cmds.cmd);
	else if (i != -1)
		cmd_not_f(cmds);
	if (cmds.sep == 1)
		parse_line(cmds.rst, envp);
}

void	prep_pipe(int p1, int p2, int mode)
{
	close(p1);
	dup2(p2, mode);
	close(p2);
}

int		into_pipe(t_cmds cmds, char ***envp)
{
	int		pipefd[2];
	int		nstdin;
	int		nstdout;
	pid_t	cpid;

	if (pipe(pipefd) == -1)
		return (ft_printf("Failure to pipe\n"));
	nstdin = dup(0);
	nstdout = dup(1);
	if ((cpid = fork()) == -1)
		return (ft_printf("Failure to fork\n"));
	if (cpid == 0)
	{
		prep_pipe(pipefd[0], pipefd[1], 1);
		single_cmd(cmds, envp);
		exit(0);
	}
	else
	{
		wait(0);
		prep_pipe(pipefd[1], pipefd[0], 0);
		parse_line(cmds.rst, envp);
	}
	dup2(nstdin, 0);
	dup2(nstdout, 1);
	free_cmd(cmds);
	return (0);
}

int		redir_form_file(t_cmds cmds, int fd, char ***envp)
{
	int		nstdin;

	nstdin = dup(0);
	dup2(fd, 0);
	ft_dispatch(cmds, envp);
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

	if (cmds.rst == 0 || cmds.rst[0] == 0)
		return (ft_printf("parse error near \\n\n"));
	i = 0;
	while (ft_isspace(cmds.rst[i]))
		i++;
	rst_cmd.cmd = get_cmd(cmds.rst, &i);
	if ((fd = open(rst_cmd.cmd, O_RDONLY)) == -1)
		return (ft_printf("no such file or directory: %s\n", rst_cmd.cmd));
	rst_cmd.args = ft_split_free(get_args(cmds.rst, &i), 7);
	cmds.args = ft_join_tabs_free1(cmds.args, rst_cmd.args);
	if ((cmds.sep = get_sep(cmds.rst, &i)))
		rst_cmd.rst = ft_strdup(cmds.rst + i + 1 + (cmds.sep == 5));
	else
		rst_cmd.rst = 0;
	free(cmds.rst);
	cmds.rst = (cmds.sep) ? ft_strdup(rst_cmd.rst) : 0;
	free_cmd(rst_cmd);
	return (redir_form_file(cmds, fd, envp));
}

int		redir_into_file(t_cmds cmds, int fd, char ***envp)
{
	int		nstdout;

	nstdout = dup(1);
	dup2(fd, 1);
	ft_dispatch(cmds, envp);
	close(fd);
	dup2(nstdout, 1);
	close(nstdout);
	return (0);
}

int		into_file(t_cmds cmds, char ***envp, int mod)
{
	size_t	i;
	int		fd;
	t_cmds	rst_cmd;

	if (cmds.rst == 0 || cmds.rst[0] == 0)
		return (ft_printf("parse error near \\n\n"));
	i = 0;
	while (ft_isspace(cmds.rst[i]))
		i++;
	rst_cmd.cmd = get_cmd(cmds.rst, &i);
	if ((mod && (fd = open(rst_cmd.cmd, O_CREAT | O_WRONLY | O_APPEND, 0644)) == -1) ||
		(!mod && (fd = open(rst_cmd.cmd, O_CREAT | O_WRONLY, 0644)) == -1))
		return (ft_printf("permission denied: %s\n", rst_cmd.cmd));
	rst_cmd.args = ft_split_free(get_args(cmds.rst, &i), 7);
	cmds.args = ft_join_tabs_free1(cmds.args, rst_cmd.args);
	if ((cmds.sep = get_sep(cmds.rst, &i)))
		rst_cmd.rst = ft_strdup(cmds.rst + i + 1 + (cmds.sep == 5));
	else
		rst_cmd.rst = 0;
	free(cmds.rst);
	cmds.rst = (cmds.sep) ? ft_strdup(rst_cmd.rst) : 0;
	free_cmd(rst_cmd);
	return (redir_into_file(cmds, fd, envp));
}

void	ft_dispatch(t_cmds cmds, char ***envp)
{
	if (check_err(cmds))
		return ;
	if (cmds.sep == 0 || cmds.sep == 1)
		single_cmd(cmds, envp);
	if (cmds.sep == 2)
		into_pipe(cmds, envp);
	if (cmds.sep == 3)
		from_file(cmds, envp);
	if (cmds.sep == 4 || cmds.sep == 5)
		into_file(cmds, envp, cmds.sep - 4);
}

int		check_quote(char *line)
{
	int		i;
	int		inqu;
	int		indqu;

	i = 0;
	inqu = 0;
	indqu = 0;
	while (line[i])
	{
		if (line[i] == '\'' && !(indqu % 2))
			inqu += 1;
		if (line[i] == '\"' && !(inqu % 2))
			indqu += 1;
		i++;
	}
	if (inqu % 2 || indqu % 2)
		return (2);
	return (0);
}

char	*get_cmd(char *line, size_t *i)
{
	int		tab[4];
	char	*nl;

	tab[0] = 0;
	tab[1] = 0;
	tab[2] = 0;
	tab[3] = 0;
	if (!(nl = malloc(ft_strlen(line) + 1)))
		return (0);
	while (line[*i] && !tab[0])
	{
		if ((line[*i] == ' ' || ft_isinset(line[*i], SEP_SET))
			&& !(tab[1] % 2) && !(tab[2] % 2))
			tab[0] = 1;
		else if (line[*i] == '\'' && !(tab[2] % 2))
			tab[1] += 1;
		else if (line[*i] == '\"' && !(tab[1] % 2))
			tab[2] += 1;
		else
			nl[tab[3]++] = line[*i];
		if (tab[0] != 1)
			*i = *i + 1;
	}
	nl[tab[3]] = 0;
	return (nl);
}

char	*get_args(char *line, size_t *i)
{
	int		tab[4];
	char	*nl;

	tab[0] = 0;
	tab[1] = 0;
	tab[2] = 0;
	tab[3] = 0;
	if (!(nl = malloc(ft_strlen(line) + 1)))
		return (0);
	while (line[*i] && tab[0] != 1)
	{
		tab[0] = 0;
		if (((line[*i] == ' ') || ft_isinset(line[*i], SEP_SET))
			&& !(tab[1] % 2) && !(tab[2] % 2))
			tab[0] = (line[*i] == ' ') ? 7 : 1;
		if (line[*i] == '\'' && !(tab[2] % 2))
			tab[1] += 1;
		else if (line[*i] == '\"' && !(tab[1] % 2))
			tab[2] += 1;
		else if (tab[0] != 1)
			nl[tab[3]++] = (tab[0] == 7) ? tab[0] : line[*i];
		(tab[0] != 1) ? *i = *i + 1 : 0;
	}
	nl[tab[3]] = 0;
	return (nl);
}

int		get_sep(char *line, size_t *i)
{
	if (line[*i] == 0)
		return (0);
	if (line[*i] == ';')
		return (1);
	if (line[*i] == '|')
		return (2);
	if (line[*i] == '<')
		return (3);
	if (line[*i] == '>')
	{
		if (line[*i + 1] == '>')
			return (5);
		else
			return (4);
	}
	return (0);
}

int		parse_line(char *line, char ***envp)
{
	t_cmds	cmds;
	size_t	i;

	i = 0;
	while (ft_isspace(line[i]))
		i++;
	cmds.cmd = get_cmd(line, &i);
	while (ft_isspace(line[i]))
		i++;
	cmds.args = ft_split_free(get_args(line, &i), 7);
	if ((cmds.sep = get_sep(line, &i)))
		cmds.rst = ft_strdup(line + i + 1 + (cmds.sep == 5));
	else
		cmds.rst = 0;
	//int j = 0;
	//printf("%s\n", cmds.cmd);
	//while (cmds.args[j] != 0)
	//{
	//	printf("%s\n", cmds.args[j]);
	//	j++;
	//}
	//printf("%i\n", cmds.sep);
	//printf("%s\n", cmds.rst);
	free(line);
	ft_dispatch(cmds, envp);
	return (0);
}

size_t	find_dol(char *line)
{
	size_t	i;
	int		inqu;
	int		indqu;

	i = 0;
	inqu = 0;
	indqu = 0;
	while (line[i])
	{
		if (line[i] == '\'' && !(indqu % 2))
			inqu += 1;
		if (line[i] == '\"' && !(inqu % 2))
			indqu += 1;
		if (line[i] == '$' && !(inqu % 2))
			return (i);
		i++;
	}
	return (-1);
}

int		rpl_var(char **line, size_t i, size_t pdol, char *menvj)
{
	size_t	j;
	size_t	k;
	size_t	len;
	char	*nl;

	j = 0;
	k = 0;
	len = ft_strlen(*line) - ((1 + !!menvj) * pdol) + ft_strlen(menvj) + 1;
	if (!(nl = malloc(len)))
		return (0);
	while (j < len - 1)
	{
		if (j < i)
			nl[j] = *(*line + j);
		else if (k + pdol < ft_strlen(menvj))
			nl[j] = menvj[k++ + pdol];
		else if ((i + pdol) < ft_strlen(*line))
			nl[j] = *((*line) + i + pdol++);
		j++;
	}
	nl[j] = 0;
	free(*line);
	*line = nl;
	return (1);
}

int		get_var_env(char **line, size_t os, char **menv)
{
	size_t	i;
	size_t	pdol;
	size_t	j;

	if (!ft_strlen(*line) || (i = find_dol(((*line) + os))) == (size_t)-1)
		return (0);
	pdol = 1;
	while (*(*line + i + pdol + os) &&
		!ft_isinset(*(*line + i + pdol + os), STOPDOL))
		pdol++;
	if (pdol == 0)
		return (0);
	if (pdol == 1)
		return (get_var_env(line, i + 1 + os, menv));
	j = 0;
	while (menv[j] && ft_strncmp(menv[j],
		((*line) + i + 1 + os), ft_charat(menv[j], '=')))
		j++;
	if (!rpl_var(line, i + os, pdol, menv[j]))
		return (-1);
	if ((i = find_dol(((*line) + os)) == (size_t)-1))
		return (0);
	return (get_var_env(line, os, menv));
}

void	entry_loop(char ***envp)
{
	char	*line;
	char	**args;
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
	entry_loop(&nenvp);
	//system("leaks a.out");
	return (0);
}
