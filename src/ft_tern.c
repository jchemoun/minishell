/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tern.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchemoun <jchemoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 12:54:23 by jchemoun          #+#    #+#             */
/*   Updated: 2021/04/03 13:38:24 by jchemoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	tern_g_code(int status)
{
	if (WIFSIGNALED(status))
	{
		if (W_EXITCODE(WEXITSTATUS(status), status) == 131)
			g_ret = 131;
		else
			g_ret = 128 + W_EXITCODE(WEXITSTATUS(status), status);
	}
	else
		g_ret = W_EXITCODE(WEXITSTATUS(status), status);
}
