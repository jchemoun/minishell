/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchemoun <jchemoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 10:47:57 by jchemoun          #+#    #+#             */
/*   Updated: 2020/03/09 11:48:02 by jchemoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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

char	**get_args2(char *line, size_t *i)
{
	char	**args;
	char	*nl;

	if (!(args = malloc(sizeof(char *) * 1)))
		return (0);
	args[0] = 0;
	while (line[*i] && !ft_isinset(line[*i], SEP_SET))
	{
		while (line[*i] && ft_isspace(line[*i]))
			*i = *i + 1;
		if (line[*i] && !ft_isinset(line[*i], SEP_SET))
		{
			nl = get_cmd(line, i);
			args = push_back_tab_free(nl, args);
			free(nl);
		}
	}
	return (args);
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

int		parse_line(char *line, char ***envp)
{
	t_cmds	cmds;
	size_t	i;

	i = 0;
	while (ft_isspace(line[i]))
		i++;
	cmds.cmd = get_cmd(line, &i);
	while (ft_isspace(line[i]))
		i++;
	cmds.args = get_args2(line, &i);
	if ((cmds.sep = get_sep(line, &i)))
		cmds.rst = ft_strdup(line + i + 1 + (cmds.sep == 5));
	else
		cmds.rst = 0;
	free(line);
	ft_dispatch(cmds, envp);
	return (0);
}