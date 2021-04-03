/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   historia.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchemoun <jchemoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 19:51:36 by jchemoun          #+#    #+#             */
/*   Updated: 2021/04/03 13:47:11 by jchemoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	replace_line(char **buf, char *hist)
{
	int	i;

	while (**buf)
		ft_deappend(buf);
	i = 0;
	while (hist && hist[i])
	{
		ft_append(buf, hist[i]);
		i++;
	}
}

void	remove_historia_dup(t_historia_dc **historia)
{
	t_historia_dc	*prevh;

	while ((*historia)->prev)
	{
		prevh = (*historia)->prev;
		if ((*historia)->str
			&& !ft_strncmp((*historia)->str, prevh->str, 999999))
		{
			prevh->next = (*historia)->next;
			prevh->next->prev = prevh;
			free((*historia)->str);
			free((*historia));
			*historia = prevh;
		}
		else
			(*historia) = prevh;
	}
	while ((*historia)->next)
		(*historia) = (*historia)->next;
}

void	add_historia(char *line, t_historia_dc **historia)
{
	t_historia_dc	*newh;

	while ((*historia)->next)
		*historia = (*historia)->next;
	newh = malloc(sizeof(t_historia_dc));
	if (!newh)
		proper_exit(1, 1);
	newh->next = 0;
	newh->prev = (*historia);
	newh->str = 0;
	if ((*historia)->str == 0)
		(*historia)->str = ft_strdup((const char *) line);
	else
	{
		free((*historia)->str);
		(*historia)->str = ft_strdup((const char *) line);
	}
	(*historia)->next = newh;
	*historia = (*historia)->next;
	remove_historia_dup(historia);
}
