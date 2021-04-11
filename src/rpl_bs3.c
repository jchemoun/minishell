/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rpl_bs3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchemoun <jchemoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 12:58:45 by jchemoun          #+#    #+#             */
/*   Updated: 2021/04/11 13:27:59 by jchemoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	rpl_semicolon(char c)
{
	if (c == ';')
		return (5);
	else
		return (c);
}

void	reset_bs_dquote(char *nl, int *inqu, int *indqu)
{
	if (nl == 0)
	{
		*inqu = 0;
		*indqu = 0;
	}
}
