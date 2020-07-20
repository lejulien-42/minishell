/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_word_count.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frtalleu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 03:31:55 by frtalleu          #+#    #+#             */
/*   Updated: 2019/11/14 03:49:53 by frtalleu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_word_count(char *str, char *charset)
{
	int n;
	int i;

	n = 0;
	i = 0;
	while (str[i])
	{
		if (ft_is_in_base(str[i], charset) == -1)
		{
			while (str[i] != '\0' && ft_is_in_base(str[i], charset) == -1)
				i++;
			n++;
			if (str[i] == '\0')
				return (n);
		}
		i++;
	}
	return (n);
}
