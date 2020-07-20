/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frtalleu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 22:26:27 by frtalleu          #+#    #+#             */
/*   Updated: 2019/11/12 21:33:30 by frtalleu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include "libft.h"

char			*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*tab;
	unsigned int	j;

	j = 0;
	if (s == NULL || f == NULL)
		return (NULL);
	if (!(tab = malloc(sizeof(char) * (ft_strlen(s) + 1))))
		return (NULL);
	while (s[j] != 0)
	{
		tab[j] = (*f)(j, s[j]);
		j++;
	}
	tab[j] = '\0';
	return (tab);
}
