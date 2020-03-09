/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchemoun <jchemoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 11:03:43 by jchemoun          #+#    #+#             */
/*   Updated: 2020/03/09 11:35:22 by jchemoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	update_oldpwd(char *arg, char ***envp)
{
	int i;

	i = 0;
	while ((*envp)[i])
	{
		if (!ft_strncmp("OLDPWD", (*envp)[i], ft_charat((*envp)[i], '=')))
		{
			free((*envp)[i]);
			(*envp)[i] = ft_strjoin("OLDPWD=", arg + ft_charat(arg, '=') + 1);
			break ;
		}
		i++;
	}
}

void	update_pwd(char ***envp)
{
	int		i;
	char	pwd[BUF_S];

	i = 0;
	while ((*envp)[i])
	{
		if (!ft_strncmp("PWD", (*envp)[i], ft_charat((*envp)[i], '=')))
		{
			update_oldpwd((*envp)[i], envp);
			free((*envp)[i]);
			getcwd(pwd, BUF_S);
			(*envp)[i] = ft_strjoin("PWD=", pwd);
			break ;
		}
		i++;
	}
}

int		ft_cd(t_cmds cmds, char ***envp)
{
	struct stat	buf;
	char		*home;

	if (cmds.args[0] == 0)
	{
		home = get_home(*envp);
		chdir(home + 5);
		update_pwd(envp);
		free_cmd(cmds);
		return (0);
	}
	if (stat(cmds.args[0], &buf) == -1)
		return (ft_werrorfree("no such file or directory:", cmds, 127));
	if (get_perm(buf, 0))
	{
		chdir(cmds.args[0]);
		update_pwd(envp);
		free_cmd(cmds);
	}
	else
		return (ft_werrorfree("permission denied:", cmds, 126));
	return (0);
}
