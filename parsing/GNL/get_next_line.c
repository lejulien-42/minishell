/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frtalleu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 03:57:23 by frtalleu          #+#    #+#             */
/*   Updated: 2020/07/20 12:10:46 by frtalleu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "get_next_line.h"
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include "../libft/libft.h"

char	*ft_read(int fd, char **rest)
{
	char			*buff;
	int				size;
	char			*tmp;
	int BUFFER_SIZE = 1024;

	size = BUFFER_SIZE;
	if (!(buff = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (NULL);
	while (size == BUFFER_SIZE && ft_checkline(*rest) == -1)
	{
		size = read(fd, buff, BUFFER_SIZE);
		buff[size] = '\0';
		if (!(tmp = ft_strjoin(*rest, buff)))
			return (NULL);
		if (*rest != 0)
			free(*rest);
		if (!(*rest = ft_strdup(tmp)))
			return (NULL);
		free(tmp);
	}
	free(buff);
	return (*rest);
}

int		get_next_line(int fd, char **line)
{
	static char *rest = NULL;
	t_char		*st;

	if (line)
		*line = NULL;
	if (fd < 0 || read(fd, NULL, 0) == -1
		|| !(rest = ft_read(fd, &rest)) || !line)
		return (-1);
	if (ft_checkline(rest) == -1)
	{
		*line = rest;
		rest = NULL;
		return (0);
	}
	if (!(st = ft_cut(rest)))
		return (-1);
	if (!(st->lin))
		return (-1);
	*line = st->lin;
	rest = st->stat;
	free(st);
	return (1);
}
