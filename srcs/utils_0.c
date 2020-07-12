/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_0.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 19:20:01 by lejulien          #+#    #+#             */
/*   Updated: 2020/07/12 21:54:56 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void
	ft_putstr(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		write(1, &str[i], 1);
		i++;
	}
}

int
	ft_strcmp(const char *s1, const char *s2)
{
	int index;

	index = 0;
	while (s2[index] && s1[index])
	{
		if (s1[index] == s2[index])
		{
			index++;
		}
		else
			return ((unsigned char)s1[index] - (unsigned char)s2[index]);
	}
	if (s1[index] == '\0' || s2[index] == '\0')
	{
		return ((unsigned char)s1[index] - (unsigned char)s2[index]);
	}
	return (0);
}

void
	ft_putchar(char c, int fd)
{
	write(fd, &c, 1);
}

void
	ft_strcpy(char *dest, char *src)
{
	int i;

	i = 0;
	if (!src || !dest)
		return ;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

void
	ft_putnbr_fd(int nb, int fd)
{
	unsigned int dnb;

	if (nb < 0)
	{
		ft_putchar('-', fd);
		dnb = nb * (-1);
	}
	else
		dnb = nb;
	if (dnb >= 10)
	{
		ft_putnbr_fd(dnb / 10, fd);
		ft_putchar(dnb % 10 + '0', fd);
	}
	else
		ft_putchar(dnb + '0', fd);
}
