/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchemoun <jchemoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 11:05:48 by jchemoun          #+#    #+#             */
/*   Updated: 2020/03/09 11:37:02 by jchemoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	replace_free_intab(char ***tab, char *src, int pos)
{
	free((*tab)[pos]);
	(*tab)[pos] = ft_strdup(src);
}

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
