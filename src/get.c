/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchemoun <jchemoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 10:53:43 by jchemoun          #+#    #+#             */
/*   Updated: 2021/04/03 13:46:31 by jchemoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	get_perm(struct stat buf, int f)
{
	static struct stat	min;

	if (f)
	{
		stat("./minishell", &min);
		return (1);
	}
	if ((buf.st_mode & S_IFMT) == S_IFDIR)
		return (2);
	if (buf.st_uid == min.st_uid && buf.st_mode & 00100)
		return (1);
	if (buf.st_uid != min.st_uid
		&& buf.st_gid == min.st_gid && buf.st_mode & 00010)
		return (1);
	if (buf.st_uid != min.st_uid
		&& buf.st_gid != min.st_gid && buf.st_mode & 00001)
		return (1);
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

char	*get_home(char **envp)
{
	int	j;

	j = 0;
	while (envp[j] && ft_strncmp(envp[j], "HOME", ft_charat(envp[j], '=')))
		j++;
	return (envp[j]);
}

int	check_err(t_cmds cmds)
{
	int	i;

	i = 0;
	if (cmds.sep > 1 && (cmds.rst == 0 || cmds.rst[0] == 0))
	{
		ft_werror_token(cmds, cmds.rst[i], 258);
		return (1);
	}
	while (cmds.sep > 0 && cmds.rst[i] == ' ')
		i++;
	if (cmds.rst && ft_isinset(cmds.rst[i], SEP_SET))
	{
		ft_werror_token(cmds, cmds.rst[i], 258);
		return (1);
	}
	return (0);
}
