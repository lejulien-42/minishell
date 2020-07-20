/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frtalleu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 13:59:52 by frtalleu          #+#    #+#             */
/*   Updated: 2019/11/14 23:52:14 by frtalleu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdio.h>
#include <string.h>

char	*ft_strnstr(const char *str, const char *to_find, size_t n)
{
	unsigned int i;
	unsigned int j;

	i = 0;
	if (to_find[0] == '\0')
		return ((char*)str);
	if (n == 0)
		return (0);
	while (str[i] != '\0')
	{
		j = 0;
		while (to_find[j] == str[i + j] && (i + j) < n)
		{
			if (to_find[j + 1] == '\0')
				return ((char*)&str[i]);
			j++;
		}
		i++;
	}
	return (0);
}
