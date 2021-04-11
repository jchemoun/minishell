/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchemoun <jchemoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 10:52:43 by jchemoun          #+#    #+#             */
/*   Updated: 2021/04/11 13:28:13 by jchemoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <signal.h>
# include <fcntl.h>
# include <curses.h>
# include <term.h>
# include <termios.h>
# include <libft.h>
# include <ft_printf.h>

# define SEP_SET ";|<>\0"
# define STOPDOL " \"'+;,<>/\\.%&|:$?\0"
# define BUF_S 100

int	g_ret;

typedef struct s_sig
{
	int			signum;
	int			st;
}				t_sig;

typedef struct s_cmds
{
	char		*cmd;
	char		**args;
	int			sep;
	char		*rst;
}				t_cmds;

typedef struct s_historia_dc
{
	char					*str;
	struct s_historia_dc	*prev;
	struct s_historia_dc	*next;
}				t_historia_dc;

int				ft_isspace(char c);
size_t			ft_charat(const char *str, int c);
void			free_cmd(t_cmds cmds);
void			free_zero(void **ptr);
char			*ft_strjoinfree2(const char *s1, const char *s2);
char			*read_line(void);
char			*get_path(char **envp);
int				simple_exec(t_cmds cmds, char **envp, char *cp);
int				get_perm(struct stat buf, int f);
char			*isinpath(t_cmds cmds, char **envp, int *j);
int				isindir(t_cmds cmds, int *j);
int				check_quote(char *line);
char			*get_cmd(char *line, size_t *i);
char			*get_args(char *line, size_t *i);
char			**get_args2(char *line, size_t *i);
int				get_sep(char *line, size_t *i);
int				parse_line(char *line, char ***envp);
size_t			find_dol(char *line);
int				rpl_var(char **line, size_t i, size_t pdol, char *menvj);
int				get_var_env(char **line, size_t os, char **menv);
void			var_env_ligne(char **line, char ***envp);
void			entry_loop(char ***envp);
char			*get_home(char **envp);
int				check_err(t_cmds cmds);

void			ft_dispatch(t_cmds cmds, char ***envp);

int				single_cmd(t_cmds cmds, char ***envp);
int				into_pipe(t_cmds cmds, char ***envp);
int				from_file(t_cmds cmds, char ***envp);
int				into_file(t_cmds cmds, char ***envp, int mod);

int				is_builtin(char *cmd);
void			init_builtin(int (*(*builtin)[8])(t_cmds, char ***envp));

int				ft_echo(t_cmds cmds, char ***envp);
int				ft_cd(t_cmds cmds, char ***envp);
int				ft_pwd(t_cmds cmds, char ***envp);
int				ft_export(t_cmds cmds, char ***envp);
int				ft_unset(t_cmds cmds, char ***envp);
int				ft_env(t_cmds cmds, char ***envp);
int				ft_exit(t_cmds cmds, char ***envp);
int				ft_empty_cmd(t_cmds cmds, char ***envp);
int				cmd_not_f(t_cmds cmds);

void			signal_callback_handler(int signum);
void			sign3(int signum);
void			global_change(int signum);
void			crtl_d_exit(void);
void			crtl_c_buf(char **buf);

int				ft_werror(char *str, t_cmds cmds, int rcode);
int				ft_werrornoarg(char *str, t_cmds cmds, int rcode);
int				ft_werror_token(t_cmds cmds, int token, int rcode);
int				ft_werror_file_from(char ***envp, t_cmds cmds,
					t_cmds rst_cmds, int rcode);
int				ft_werrorfree(char *str, t_cmds cmds, int rcode);
int				ft_werrornoargfree(char *str, t_cmds cmds, int rcode);
int				ft_werror_file(char ***envp, t_cmds cmds,
					t_cmds rst_cmds, int rcode);

char			**ft_copy(char **envp);
void			replace_free_intab(char ***tabb, char *src, int pos);
int				ft_nbl(char **envp);
char			**ft_copy(char **envp);
char			**ft_sort_env(char **fenv);
char			*add_egg(char *arg);

int				ft_wertoken(t_cmds cmds, int token, int rcode);
char			**ft_base_env(void);
void			shlvl_add(char **envp);

void			rpl_bs_ligne(char **line);
void			rpl_bs_cmds(t_cmds cmds);
int				rpl_bs_dquote(char *line, char *nl, int *j, int *k);

void			enable_rawmode(void);
void			disable_rawmode(void);

void			proper_exit(unsigned char exit_code, int error);

void			get_char(char *c, char **buf, t_historia_dc **historia);
char			*read_linev2(t_historia_dc **historia);
void			arrow_up(char **buf, t_historia_dc **historia);
void			arrow_down(char **buf, t_historia_dc **historia);
void			arrow_lr(char **buf);
void			add_historia(char *line, t_historia_dc **historia);
void			ft_deappend(char **buf);
void			ft_append(char **buf, char c);
void			replace_line(char **buf, char *hist);

void			tern_g_code(int status);
int				find_semicolon(char *line);
int				which_bs(char c, char *set);
char			rpl_semicolon(char c);
void			reset_bs_dquote(char *nl, int *inqu, int *indqu);

#endif
