/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrow.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchemoun <jchemoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 12:42:36 by jchemoun          #+#    #+#             */
/*   Updated: 2021/04/03 12:43:04 by jchemoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	arrow_lr(char **buf)
{
	(void)buf;
}

void	arrow_down(char **buf, t_historia_dc **historia)
{
	if ((*historia)->next == 0)
		return ;
	*historia = (*historia)->next;
	replace_line(buf, (*historia)->str);
}

void	arrow_up(char **buf, t_historia_dc **historia)
{
	if ((*historia)->prev == 0)
		return ;
	if ((*historia)->next == 0)
	{
		if ((*historia)->str == 0)
			(*historia)->str = ft_strdup((const char *) *buf);
		else
		{
			free((*historia)->str);
			(*historia)->str = ft_strdup(*buf);
		}
	}
	*historia = (*historia)->prev;
	replace_line(buf, (*historia)->str);
}
