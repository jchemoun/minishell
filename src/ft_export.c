/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchemoun <jchemoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 11:01:44 by jchemoun          #+#    #+#             */
/*   Updated: 2020/03/09 11:03:16 by jchemoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_displayfree(char **fenv)
{
	int i;

	i = 0;
	while (fenv[i])
	{
		ft_printf("%s\n", fenv[i]);
		i++;
	}
	free_tab(fenv);
}

int		err_id_var(char *arg)
{
	ft_putstr_fd("minishell: export: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(" : identifiant non valable\n", 2);
	g_ret = 1;
	return (1);
}

int		check_var(char *arg)
{
	int i;

	i = 0;
	if (arg[0] > 47 && arg[0] < 58)
		return (0);
	while (arg[i] && arg[i] != '=')
	{
		if (!ft_isalnum(arg[i]) && (arg[i] != '=' && i != 0))
			return (0);
		i++;
	}
	return (1);
}

void	ft_export_if(char *arg, char ***envp)
{
	int	i;
	int	eg[2];
	int	found;

	i = 0;
	eg[0] = ((int)ft_charat(arg, '=') == -1 ?
		(int)ft_strlen(arg) : (int)ft_charat(arg, '='));
	found = 0;
	while ((*envp)[i])
	{
		eg[1] = ft_charat((*envp)[i], '=');
		if (!ft_strncmp((*envp)[i], arg, eg[0]) &&
			eg[0] == (eg[1] == -1 ? (int)ft_strlen((*envp)[i]) : eg[1]))
		{
			found = 1;
			if (eg[0] != (int)ft_strlen(arg))
				replace_free_intab(envp, arg, i);
		}
		i++;
	}
	if (found == 0)
	{
		(*envp) = push_front_tab_free2(add_egg(arg), (*envp));
	}
}

int		ft_export(t_cmds cmds, char ***envp)
{
	size_t	j;
	int		ret;

	j = 0;
	ret = 0;
	if (cmds.args[0] == 0)
	{
		ft_displayfree(ft_sort_env(ft_copy(*envp)));
		free_cmd(cmds);
		return (0);
	}
	while (cmds.args[j])
	{
		if (check_var(cmds.args[j]))
			ft_export_if(cmds.args[j], envp);
		else
			ret = err_id_var(cmds.args[j]);
		j++;
	}
	free_cmd(cmds);
	return (ret);
}
