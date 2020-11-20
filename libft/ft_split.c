/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frtalleu <frtalleu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 14:34:10 by frtalleu          #+#    #+#             */
/*   Updated: 2020/11/20 15:34:43 by frtalleu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

int
	count_word(char *st, char c)
{
	int i;
	int res;

	i = 0;
	res = 0;
	while (st[i] != '\0')
	{
		if (st[i] == c)
		{
			res++;
			while (st[i] == c)
				i++;
		}
		i++;
	}
	return (res);
}

char
	**fill_split(char **tab, char *str, char c)
{
	int i;
	int j;
	int word;

	word = 0;
	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		while (str[i + j] != c && str[i + j] != '\0')
			j++;
		while (str[i + j] == c)
			j++;
		if (str[i + j - 1] == c)
			str[i + j - 1] = '\0';
		tab[word++] = ft_strtrim(&str[i], &c);
		i = i + j;
		j = 0;
	}
	free(str);
	tab[word] = 0;
	return (tab);
}

char
	**ft_split(const char *str, const char c)
{
	char	*st;
	int		nb_words;
	char	**res;

	st = ft_strdup(str);
	nb_words = count_word(st, c);
	if (!(res = malloc(sizeof(char *) * (nb_words + 1))))
		return (NULL);
	return (fill_split(res, st, c));
}
