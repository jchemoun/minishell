/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   historia.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchemoun <jchemoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 19:51:36 by jchemoun          #+#    #+#             */
/*   Updated: 2021/04/01 19:59:45 by jchemoun         ###   ########.fr       */
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
}

void	arrow_up(char **buf, t_historia_dc **historia)
{
	if ((*historia)->prev == 0)
		return ;
	if ((*historia)->next == 0)
		(*historia)->str = *buf;
	*historia = (*historia)->prev;
}

void	add_historia(char *ligne, t_historia_dc **historia)
{
	
}
