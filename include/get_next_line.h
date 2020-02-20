/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchemoun <jchemoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 14:28:49 by jchemoun          #+#    #+#             */
/*   Updated: 2020/02/13 13:16:44 by jchemoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H

# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# define I 0
# define J 1
# define LEN 2
# define FOUND 3
# define NAT 4

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

char	*ft_init(int *found);
int		ft_foundn(char *str, int size, int *found);
char	*ft_realloc(char *str, int len, int size);
void	ft_tabinit(int tab[5]);
int		ft_fill(char **stc, char **line, char **buf, int size);
int		ft_empty(char **stc, char **line);
int		get_next_line(int fd, char **line);
int		get_next_line_cd(int fd, char **line);

#endif
