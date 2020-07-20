/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frtalleu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 05:23:14 by frtalleu          #+#    #+#             */
/*   Updated: 2019/11/12 23:54:26 by frtalleu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include "libft.h"

char			*ft_strjoin(char const *s1, char const *s2)
{
	unsigned int	i;
	char			*j;
	char			*tab;

	if (!s1 && !s2)
		return (0);
	if (!s1)
		return (ft_strdup((char *)s2));
	if (!s2)
		return (ft_strdup((char *)s1));
	i = ft_strlen(s1) + ft_strlen(s2);
	if (!(tab = malloc((i + 1) * (sizeof(char)))))
		return (NULL);
	j = tab;
	while (*s1 != '\0')
		*j++ = *s1++;
	while (*s2 != '\0')
		*j++ = *s2++;
	*j = '\0';
	return (tab);
}
