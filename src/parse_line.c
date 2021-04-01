/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchemoun <jchemoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 10:47:57 by jchemoun          #+#    #+#             */
/*   Updated: 2021/04/01 17:33:40 by jchemoun         ###   ########.fr       */
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
	int		tabb[4];
	char	*nl;

	tabb[0] = 0;
	tabb[1] = 0;
	tabb[2] = 0;
	tabb[3] = 0;
	if (!(nl = malloc(ft_strlen(line) + 1)))
		return (0);
	while (line[*i] && !tabb[0])
	{
		if ((line[*i] == ' ' || ft_isinset(line[*i], SEP_SET))
			&& !(tabb[1] % 2) && !(tabb[2] % 2))
			tabb[0] = 1;
		else if (line[*i] == '\'' && !(tabb[2] % 2))
			tabb[1] += 1;
		else if (line[*i] == '\"' && !(tabb[1] % 2))
			tabb[2] += 1;
		else
			nl[tabb[3]++] = line[*i];
		if (tabb[0] != 1)
			*i = *i + 1;
	}
	nl[tabb[3]] = 0;
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

	var_env_ligne(&line, envp);
	i = 0;
	while (ft_isspace(line[i]))
		i++;
	cmds.cmd = get_cmd(line, &i);
	while (ft_isspace(line[i]))
		i++;
	cmds.args = get_args2(line, &i);
	cmds.sep = get_sep(line, &i);
	cmds.rst = cmds.sep ? ft_strdup(line + i + 1 + (cmds.sep == 5)) : 0;
	free(line);
	rpl_bs_cmds(cmds);
	ft_dispatch(cmds, envp);
	return (0);
}
