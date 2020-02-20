/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchemoun <jchemoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 11:36:37 by jchemoun          #+#    #+#             */
/*   Updated: 2019/10/25 13:23:09 by jchemoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list *new;

	if (lst)
	{
		if (!(new = ft_lstnew(f(lst->content))))
			ft_lstdelone(lst, del);
		new->next = ft_lstmap(lst->next, f, del);
		return (new);
	}
	return (NULL);
}
