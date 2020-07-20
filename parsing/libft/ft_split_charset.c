/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_charset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frtalleu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 01:46:40 by frtalleu          #+#    #+#             */
/*   Updated: 2019/11/14 03:46:53 by frtalleu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	word_length(char *start, char *charset)
{
	int i;

	i = 0;
	while (start[i] && ft_is_in_base(start[i], charset) == -1)
		i++;
	return (i);
}

static char	**init(int *word, int *i, char *s, char *cs)
{
	char **tab;

	*word = -1;
	*i = 0;
	if (!(tab = (char**)malloc(sizeof(char*) * (ft_word_count(s, cs) + 1))))
		return (NULL);
	return (tab);
}

char		**ft_split_charset(char *str, char *charset)
{
	int		i;
	int		word;
	int		len;
	char	**tab;
	int		j;

	tab = init(&word, &i, str, charset);
	while (++word < ft_word_count(str, charset))
	{
		while (ft_is_in_base(str[i], charset) != -1)
			i++;
		len = word_length(&str[i], charset);
		if (len >= 0)
		{
			if (!(tab[word] = (char*)malloc(sizeof(char) * (len + 1))))
				return (NULL);
			j = -1;
			while (++j < len)
				tab[word][j] = str[i + j];
			tab[word][j] = '\0';
		}
		i += len;
	}
	tab[ft_word_count(str, charset)] = 0;
	return (tab);
}
