/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchemoun <jchemoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 17:16:45 by jchemoun          #+#    #+#             */
/*   Updated: 2020/02/20 13:24:32 by jchemoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <libft.h>
#include <ft_printf.h>
#include <get_next_line.h>

# define SEP_SET ";|<>\0"
# define STOPDOL " \"'+;,<>/\\.%&|:$\0"

typedef struct	s_sig
{
	int		signum;
	int		st;
}				t_sig;

typedef struct	s_cmds
{
	char	*cmd;
	char	**args;
	int		sep;
	char	*rst;
}				t_cmds;

int		ft_isspace(char c)
{
	if (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r' || c == ' ')
		return (1);
	return (0);
}

void	signal_callback_handler(int signum)
{
	ft_printf("\n> ");
}

char	*read_line(void)
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
			exit(1);
	}
	return (0);
}
/*
void	ft_echo()
{
	int i;

	i = 0;

}

void	parse_input(char *line, char **envp)
{
	while (ft_isspace(*line))
		line++;
	if (!ft_strncmp(line, "echo", 4))
		ft_echo(line + 4);
	else if (!ft_strncmp(line, "cd", 2))
		ft_cd();
	else if (!ft_strncmp(line, "pwd", 3))
		ft_pwd();
	else if (!ft_strncmp(line, "export", 6))
		ft_export();
	else if (!ft_strncmp(line, "unset", 5))
		ft_unset();
	else if (!ft_strncmp(line, "env", 3))
		ft_env();
	else if (!ft_strncmp(line, "exit", 4))
		ft_exit();
	else if (!ft_strncmp(line, "./", 2))
		ft_exec();
	else if (!ft_strncmp(line, "'", 1))
		ft_bquote();
	else if (!ft_strncmp(line, "\"", 1))
		ft_dquote();
}*/

char	*ft_strjoin_free()
{
	return (0);
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
		if ((line[*i] == ' ' || ft_isinset(line[*i], SEP_SET))
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

int		parse_line(char *line, char **envp)
{
	t_cmds	cmds;
	//size_t	size;
	size_t	i;

	//size = ft_strlen(line);
	i = 0;
	//if (check_quote(line))
	//	return (1);
	// 1 : avance tous whitspace
	while (ft_isspace(line[i]))
		i++;
	// 2 : commande = tous jusqu'a un espace ou un sep qui n'est pas entre quote ou dquote
	cmds.cmd = get_cmd(line, &i);
	// 3 : avance tous whitspace
	while (ft_isspace(line[i]))
		i++;
	// BALEC => 4 : option = tous ce qui match une option jusqu'qu prochain espace qui n'est pas entre quote ou dquote
	// 5 : args = tous le reste, separe par des espaces, jusqu'a un separator qui n'est pas entre quote ou dquote
	//printf("%s\n", line + i);
	//printf("%s\n", "\7");
	cmds.args = ft_split(get_args(line, &i), 7);
	//printf("%i	%p\n", line[i], cmds.args);
	// 6 : separator = "SEPSET"
	if ((cmds.sep = get_sep(line, &i)))
		cmds.rst = ft_strdup(line + i + 1 + (cmds.sep == 5));
	else
		cmds.rst = 0;
	//printf("%s\n", cmds.rst);
	// 7 : loop 1
	int j = 0;
	printf("%s\n", cmds.cmd);
	while (cmds.args[j] != 0)
	{
		printf("%s\n", cmds.args[j]);
		j++;
	}
	return (0);
}

size_t	ft_charat(const char *str, int c)
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
/*
char	*get_var_env(char *cmd, char **menv)
{
	int i;
	int size;
	char *tmp;
	int len;
	int j;
	i = 0;
	size = 0;
	len = 0;
	j = 0;
	while(cmd[i])
	{
		if (cmd[i] == '$' && (cmd[i + 1] != ' ' && cmd[i + 1] != '\0' && cmd[i + 1] != ';'))
		{
			while(!ft_strchr(" ;\"'", cmd[i + size]) && cmd[i + size])
				size++;
			//printf("%i\n", i + size);
			while(menv[j] && ft_strncmp(menv[j], &cmd[i + 1], ft_charat(menv[j], '=')) != 0)
				j++;
			//printf("%s\n", menv[j]);
			if (!menv[j])
				return (0);
			len = ft_strlen(cmd) + ft_strlen(menv[j]) - ((size) * 2);
			//printf("%i\n", len);
			if(!(tmp = calloc(1, sizeof(char) * (len + 1))))
				return (0);
			memcpy(tmp, cmd, i);
			len = ft_strlen(menv[j]) - (size + 1);
			ft_memcpy(&tmp[i], &menv[j][size], (len + 1));
			ft_memcpy(&tmp[i + len], &cmd[i + size], (ft_strlen(&cmd[i + size])));
			//printf("%s\n", tmp);
			free(cmd);
			cmd = tmp;
			i = 0;
		}
		i++;
	}
	printf("%s\n", cmd);
	return (cmd);
}*/

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

	if (!ft_strlen(*line) || (i = find_dol(((*line) + os))) == -1)
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
	if ((i = find_dol(((*line) + os)) == -1))
		return (0);
	return (get_var_env(line, os, menv));
}

void	entry_loop(char **envp)
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
		get_var_env(&line, 0, envp);
		printf("POSTVAR :%s\n", line);
		//stop = parse_line(line, envp);
		//printf("%s\n", line);
		//free(line);
	}
	//}
}

int	main(int argc, char **argv, char **envp)
{
	signal(SIGINT, signal_callback_handler);

	char** env;
	for(env=envp;*env!=0;env++)
	{
		char* thisEnv = *env;
		printf("%s\n",thisEnv);
	}
	//execve("/bin/echo", argv, envp);
	entry_loop(envp);
	//char *str;
	//str = malloc(10000);
	//int i = 0;
	//while (i < 9)
	//{
	//	str[i] = 48;
	//	i++;
	//}
	//str[i] = 0;
	//printf("%s\n", str);
	//free(str);
	//system("leaks a.out");
	return (0);
}
