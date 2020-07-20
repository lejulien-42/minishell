/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frtalleu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 16:27:53 by frtalleu          #+#    #+#             */
/*   Updated: 2019/11/13 01:01:07 by frtalleu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	char	*d;
	char	*s;
	size_t	n;
	size_t	lend;

	d = dest;
	s = (char *)src;
	n = size;
	while (n-- != 0 && *d != '\0')
		d++;
	lend = d - dest;
	n = size - lend;
	if (n == 0)
		return (lend + ft_strlen(src));
	while (*s != '\0')
	{
		if (n != 1)
		{
			*d++ = *s;
			n--;
		}
		s++;
	}
	*d = '\0';
	return (lend + (s - src));
}
