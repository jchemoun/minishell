/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchemoun <jchemoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 10:59:11 by jchemoun          #+#    #+#             */
/*   Updated: 2021/04/05 12:42:13 by jchemoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	free_cmd(t_cmds cmds)
{
	free(cmds.cmd);
	free_tab(cmds.args);
}

int	ft_werrornoargfree(char *str, t_cmds cmds, int rcode)
{
	ft_werrornoarg(str, cmds, rcode);
	free_cmd(cmds);
	g_ret = rcode;
	return (1);
}

int	ft_werrorfree(char *str, t_cmds cmds, int rcode)
{
	ft_werror(str, cmds, rcode);
	free_cmd(cmds);
	g_ret = rcode;
	return (1);
}

void	free_zero(void **ptr)
{
	free(*ptr);
	*ptr = 0;
}
