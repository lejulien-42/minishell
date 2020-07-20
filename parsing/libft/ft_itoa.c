/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frtalleu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 17:18:14 by frtalleu          #+#    #+#             */
/*   Updated: 2019/11/12 01:59:17 by frtalleu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static char	*ft_itoa2(unsigned int nu, int n, int i)
{
	char *str;

	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	if (!(str = malloc(sizeof(char) * (i + 1))))
		return (NULL);
	str[i] = '\0';
	while (nu >= 10)
	{
		i--;
		str[i] = (nu % 10) + 48;
		nu = nu / 10;
	}
	i--;
	str[i] = nu + 48;
	i--;
	if (i == 0)
		str[0] = '-';
	return (str);
}

char		*ft_itoa(int n)
{
	unsigned int	nu;
	int				i;

	i = 0;
	if (n <= 0)
	{
		i++;
		nu = -n;
	}
	else
		nu = n;
	return (ft_itoa2(nu, n, i));
}
