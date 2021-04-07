/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchemoun <jchemoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 11:06:39 by jchemoun          #+#    #+#             */
/*   Updated: 2021/04/07 12:17:54 by jchemoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_env(t_cmds cmds, char ***envp)
{
	size_t	i;

	i = 0;
	free_cmd(cmds);
	while ((*envp)[i])
	{
		if ((int)ft_charat((*envp)[i], '=') != -1)
			ft_printf("%s\n", (*envp)[i]);
		i++;
	}
	return (0);
}

char	**ft_base_env(void)
{
	char	**newenv;
	char	pwd[BUF_S];

	newenv = malloc(sizeof(char *) * (4));
	if (!newenv)
		return (NULL);
	newenv[0] = ft_strdup("OLDPWD=");
	getcwd(pwd, BUF_S);
	newenv[1] = ft_strjoin("PWD=", pwd);
	newenv[2] = ft_strdup("SHLVL=1");
	newenv[3] = 0;
	return (newenv);
}

void	shlvl_add(char **envp)
{
	int		i;
	int		lvl;
	char	*nlvl;

	i = 0;
	while (ft_strncmp(envp[i], "SHLVL=", 6))
		i++;
	if (ft_strncmp(envp[i], "SHLVL=", 6))
		return ;
	lvl = ft_atoi(envp[i] + 6);
	nlvl = ft_strjoinfree2("SHLVL=", ft_itoa(lvl + 1));
	free(envp[i]);
	envp[i] = nlvl;
}
