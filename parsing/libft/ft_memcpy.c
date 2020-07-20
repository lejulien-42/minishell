/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frtalleu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 13:15:25 by frtalleu          #+#    #+#             */
/*   Updated: 2019/11/12 04:39:20 by frtalleu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdio.h>
#include <string.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char *ptr;
	unsigned char *pt;

	ptr = (unsigned char *)dest;
	pt = (unsigned char *)src;
	if (dest == src)
		return (dest);
	while (n-- > 0)
	{
		*ptr = *pt;
		pt++;
		ptr++;
	}
	return (dest);
}
