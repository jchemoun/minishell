/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchemoun <jchemoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 10:58:28 by jchemoun          #+#    #+#             */
/*   Updated: 2020/03/09 11:51:07 by jchemoun         ###   ########.fr       */
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

char		*isinpath(t_cmds cmds, char **envp, int *j)
{
	struct stat	buf;
	char		**paths;
	char		*nl;
	int			i;

	if (!cmds.cmd || ft_charat(cmds.cmd, '/') != (size_t)-1)
		return (0);
	if (!(paths = ft_split(get_path(envp), ':')))
		return (0);
	i = -1;
	while (paths[++i])
	{
		if (stat(nl = ft_strjoinfree2(paths[i],
			ft_strjoin("/", cmds.cmd)), &buf) == -1)
			free(nl);
		else
			break ;
		nl = 0;
	}
	free_tab(paths);
	if (get_perm(buf, 0))
		return (nl);
	else if (nl != 0)
		*j = 0 - !!ft_werrorfree("permission denied:", cmds, 126);
	return (0);
}

int			isindir(t_cmds cmds, char **envp, int *j)
{
	int			i;
	struct stat	buf;

	if ((i = ft_charat(cmds.cmd, '/')) == -1)
		return (0);
	if (stat(cmds.cmd, &buf) == -1)
	{
		*j = -1;
		ft_werror("no such file or directory:", cmds, 127);
		free_cmd(cmds);
		return (0);
	}
	if ((i = get_perm(buf, 0)) == 1)
		return (1);
	else
	{
		*j = -1;
		i == 0 ? ft_werror("permission denied:", cmds, 126) :
			ft_werror("is a directory", cmds, 126);
		free_cmd(cmds);
	}
	return (0);
	(void)envp;
}
