/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 10:46:37 by jchemoun          #+#    #+#             */
/*   Updated: 2020/11/02 15:09:42 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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

void	rpl_gbl(char **line, size_t i, size_t pdol, char *dol)
{
	size_t	j;
	size_t	k;
	size_t	len;
	char	*nl;

	j = 0;
	k = 0;
	len = ft_strlen(*line) - pdol + ft_strlen(dol) + 2;
	if (!(nl = malloc(len)))
		return ;
	while (j < len - 1)
	{
		if (j < i)
			nl[j] = *(*line + j);
		else if (k < ft_strlen(dol))
			nl[j] = dol[k++];
		else if ((i + pdol++) < ft_strlen(*line))
			nl[j] = *((*line) + i + pdol);
		j++;
	}
	nl[j] = 0;
	free(*line);
	free(dol);
	*line = nl;
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
	if (pdol == 1 && *(*line + i + pdol + os) == '?')
		rpl_gbl(line, i + os, pdol, ft_itoa(g_ret));
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

void	var_env_ligne(char **line, char ***envp)
{
	int		stp;
	char	*l2;
	char	*l3;

	stp = ft_charat(*line, ';');
	if (stp != -1)
	{
		l2 = ft_strdnup(*line, ';');
		l3 = ft_strdnup(*line + stp, 99999);
	}
	else
	{
		l2 = ft_strdup(*line);
		l3 = malloc(1);
		l3[0] = 0;
	}
	rpl_bs_ligne(&l2);
	get_var_env(&l2, 0, *envp);
	free(*line);
	*line = ft_strjoin(l2, l3);
	free(l2);
	free(l3);
}
