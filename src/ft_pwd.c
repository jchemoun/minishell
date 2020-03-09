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

int		ft_pwd(t_cmds cmds, char ***envp)
{
	char pwd[BUF_S];

	if (!(getcwd(pwd, BUF_S)))
		return (ft_werrorfree("Error in getcwd:", cmds, 1));
	free_cmd(cmds);
	ft_printf("%s\n", pwd);
	return (0);
	(void)envp;
}
