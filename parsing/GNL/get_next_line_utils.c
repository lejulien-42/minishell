/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frtalleu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 03:58:37 by frtalleu          #+#    #+#             */
/*   Updated: 2020/01/15 23:50:47 by frtalleu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <unistd.h>
#include "get_next_line.h"
#include <stdlib.h>
#include "../libft/libft.h"

int		ft_checkline(char *str)
{
	int				i;

	i = 0;
	if (!str || str[i] == '\0')
		return (-1);
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

t_char	*ft_cut(char *str)
{
	t_char			*res;
	int				i;

	if (!(res = malloc(sizeof(t_char))))
		return (NULL);
	i = ft_checkline(str);
	str[i] = '\0';
	if (!(res->lin = ft_strdup(str)))
		return (NULL);
	i++;
	if (!(res->stat = ft_strdup(&str[i])))
		return (NULL);
	free(str);
	return (res);
}
