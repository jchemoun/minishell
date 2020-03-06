/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchemoun <jchemoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 10:52:43 by jchemoun          #+#    #+#             */
/*   Updated: 2020/03/06 15:36:00 by jchemoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <stdlib.h>
# include <signal.h>
# include <fcntl.h>
# include <libft.h>
# include <ft_printf.h>
# include <get_next_line.h>

# define SEP_SET ";|<>\0"
# define STOPDOL " \"'+;,<>/\\.%&|:$?\0"
# define BUF_S 100

typedef struct	s_sig
{
	int			signum;
	int			st;
}				t_sig;

typedef struct	s_cmds
{
	char		*cmd;
	char		**args;
	int			sep;
	char		*rst;
}				t_cmds;

int				ft_isspace(char c);
size_t			ft_charat(const char *str, int c);
int				free_tab(char **args);
void			free_cmd(t_cmds cmds);
char			*ft_strjoinfree2(const char *s1, const char *s2);
char			**push_front_tab(char *cp, char **args);
char			**ft_join_tabs(char **t1, char **t2);
char			*read_line(void);
char			*get_path(char **envp);
void			simple_exec(t_cmds cmds, char **envp, char *cp);
int				get_perm(struct stat buf, int f);
char			*isinpath(t_cmds cmds, char **envp, int *j);
int				isindir(t_cmds cmds, char **envp, int *j);
int				check_quote(char *line);
char			*get_cmd(char *line, size_t *i);
char			*get_args(char *line, size_t *i);
char			**get_args2(char *line, size_t *i);
int				get_sep(char *line, size_t *i);
int				parse_line(char *line, char ***envp);
size_t			find_dol(char *line);
int				rpl_var(char **line, size_t i, size_t pdol, char *menvj);
int				get_var_env(char **line, size_t os, char **menv);
void			entry_loop(char ***envp);

void			ft_dispatch(t_cmds cmds, char ***envp);

void			single_cmd(t_cmds cmds, char ***envp);
int				into_pipe(t_cmds cmds, char ***envp);
int				from_file(t_cmds cmds, char ***envp);

int				is_builtin(char *cmd);

void			ft_echo(t_cmds cmds, char ***envp);
void			ft_cd(t_cmds cmds, char ***envp);
void			ft_env(t_cmds cmds, char ***envp);
void			ft_empty_cmd(t_cmds cmds, char ***envp);
void			cmd_not_f(t_cmds cmds);

#endif
