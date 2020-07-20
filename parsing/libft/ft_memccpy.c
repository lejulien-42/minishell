/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frtalleu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 19:06:57 by frtalleu          #+#    #+#             */
/*   Updated: 2019/11/12 04:51:53 by frtalleu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	unsigned char *ptr;
	unsigned char *pt;

	ptr = (unsigned char *)dest;
	pt = (unsigned char *)src;
	while (n-- > 0)
	{
		*ptr = *pt;
		if (*pt == (unsigned char)c)
		{
			ptr++;
			return (ptr);
		}
		pt++;
		ptr++;
	}
	return (0);
}
