/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchemoun <jchemoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 11:01:44 by jchemoun          #+#    #+#             */
/*   Updated: 2020/03/09 11:03:16 by jchemoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int		ft_nbl(char **envp)
{
	int i;

	i = 0;
	while (envp[i])
		i++;
	return (i);
}

char	**ft_copy(char **envp)
{
	char	**fenv;
	int		i;

	if (!(fenv = malloc(sizeof(char *) * (ft_nbl(envp) + 1))))
		return (NULL);
	i = 0;
	while (envp[i])
	{
		fenv[i] = ft_strdup(envp[i]);
		i++;
	}
	fenv[i] = 0;
	return (fenv);
}

char	**ft_sort_env(char **fenv)
{
	int		i;
	char	*tmp;

	i = 0;
	while (fenv[i + 1])
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
	return (fenv);
}

void	ft_displayfree(char **fenv)
{
	int i;

	i = 0;
	while (fenv[i])
	{
		ft_printf("declare -x %s\n", fenv[i]);
		i++;
	}
	free_tab(fenv);
}

int		ft_export(t_cmds cmds, char ***envp)
{
	size_t	i;
	size_t	j;

	j = 0;
	if (cmds.args[0] == 0)
	{
		ft_displayfree(ft_sort_env(ft_copy(*envp)));
		free_cmd(cmds);
		return (0);
	}
	while (cmds.args[j])
	{
		i = 0;
		while ((*envp)[i] &&
			ft_strncmp((*envp)[i], cmds.args[j], ft_charat((*envp)[i], '=')))
			i++;
		if ((*envp)[i] != 0)
			(*envp)[i] = cmds.args[j];
		else
			(*envp) = push_front_tab_free(cmds.args[j], (*envp));
		j++;
	}
	free_cmd(cmds);
	return (0);
}
