/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frtalleu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 02:59:05 by frtalleu          #+#    #+#             */
/*   Updated: 2019/11/12 07:34:15 by frtalleu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

void	ft_putnbr_fd(int nb, int fd)
{
	unsigned int nbr;

	if (nb < 0)
	{
		ft_putchar_fd('-', fd);
		nbr = nb * (-1);
	}
	else
		nbr = nb;
	if (nbr >= 10)
	{
		ft_putnbr_fd(nbr / 10, fd);
		ft_putchar_fd(nbr % 10 + 48, fd);
	}
	else
		ft_putchar_fd(nbr + 48, fd);
}
