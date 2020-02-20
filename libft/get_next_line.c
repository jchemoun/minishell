/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchemoun <jchemoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 14:27:38 by jchemoun          #+#    #+#             */
/*   Updated: 2020/02/13 13:19:31 by jchemoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <get_next_line.h>
#include <libft.h>

int		ft_fill(char **stc, char **line, char **buf, int size)
{
	int		tab[5];

	ft_tabinit(tab);
	tab[LEN] = (*line != 0) ? ft_strlen(*line) : 0;
	tab[NAT] = ft_foundn(*buf, size, &tab[FOUND]);
	if (!(*line = ft_realloc(*line, tab[LEN], tab[NAT])))
		return (-1);
	if ((tab[NAT] < size) && !(*stc = malloc(size - tab[NAT])))
		return (-1);
	while (tab[I] < size)
	{
		if (tab[I] < tab[NAT])
			*(*line + tab[LEN] + tab[I]) = *(*buf + tab[I]);
		else if (tab[I] > tab[NAT])
			*(*stc + tab[J]++) = *(*buf + tab[I]);
		tab[I]++;
	}
	*(*line + tab[NAT] + tab[LEN]) = '\0';
	tab[NAT] < size ? *(*stc + tab[J]) = '\0' : 0;
	free(*buf);
	*buf = 0;
	return (tab[FOUND]);
}

int		ft_empty(char **stc, char **line)
{
	char	*new_stc;
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(*stc);
	if (!(new_stc = malloc(len + 1)))
		return (-1);
	while (i < len + 1)
	{
		*(new_stc + i) = *(*stc + i);
		i++;
	}
	free(*stc);
	*stc = 0;
	return (ft_fill(stc, line, &new_stc, len));
}

int		get_next_line(int fd, char **line)
{
	static char *stc[1024] = {0};
	char		*buf;
	int			found;
	int			r_size;

	if (BUFFER_SIZE < 1 || !(*line = ft_init(&found)))
		return (-1);
	buf = 0;
	while (!found)
	{
		if (stc[fd] != 0)
			if ((found = ft_empty(&stc[fd], line)) == -1)
				return (-1);
		if (!found)
		{
			if (!(buf = malloc(BUFFER_SIZE)))
				return (-1);
			if ((r_size = read(fd, buf, BUFFER_SIZE)) == -1)
				found = -1;
			else
				found = (r_size) ? ft_fill(&stc[fd], line, &buf, r_size) : 2;
		}
	}
	buf != 0 ? free(buf) : 0;
	return (found == 2 ? 0 : found);
}

int		get_next_line_cd(int fd, char **line)
{
	static char *stc[1024] = {0};
	char		*buf;
	int			found;
	int			r_size;

	if (BUFFER_SIZE < 1 || !(*line = ft_init(&found)))
		return (-1);
	buf = 0;
	while (!found)
	{
		if (stc[fd] != 0)
			if ((found = ft_empty(&stc[fd], line)) == -1)
				return (-1);
		if (!found)
		{
			if (!(buf = malloc(BUFFER_SIZE)))
				return (-1);
			if ((r_size = read(fd, buf, BUFFER_SIZE)) == -1)
				found = -1;
			else
				found = (r_size || (**line)) ? ft_fill(&stc[fd], line, &buf, r_size) : 2;
		}
	}
	buf != 0 ? free(buf) : 0;
	return (found == 2 ? 0 : found);
}