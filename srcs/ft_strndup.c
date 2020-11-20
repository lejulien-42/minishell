/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frtalleu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 12:14:28 by frtalleu          #+#    #+#             */
/*   Updated: 2020/07/27 12:14:29 by frtalleu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "../libft/libft.h"
#include "unistd.h"

char	*ft_strndup(char *str, int size)
{
	int		i;
	char	*st;

	i = 0;
	while (str[i] != '\0' && i < size)
		i++;
	if (!(st = malloc(sizeof(char) * (i + 1))))
		return (NULL);
	i = 0;
	while (str[i] != '\0' && i < size)
	{
		st[i] = str[i];
		i++;
	}
	st[i] = '\0';
	return (st);
}

char	*ft_strjoinbis(char const *s1, char const *s2)
{
	char	*s3;
	int		allocplace;
	char	*writeptr;

	if (!s1 && !s2)
		return (0);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	allocplace = ft_strlen(s1) + ft_strlen(s2) + 1;
	if (!(s3 = malloc(allocplace * sizeof(char))))
		return (0);
	writeptr = s3;
	while (*s1 != '\0')
	{
		*writeptr++ = *s1++;
	}
	while (*s2 != '\0')
	{
		*writeptr++ = *s2++;
	}
	*writeptr++ = '\0';
	return (s3);
}

char	*ft_strjoindf(char *s1, char *s2)
{
	char *tab;

	tab = ft_strjoinbis(s1, s2);
	free(s1);
	s1 = NULL;
	free(s2);
	s2 = NULL;
	return (tab);
}
