
#include "./libft.h"
#include <stdio.h>
#include <stdlib.h>

static int nb_word(char *str, char c)
{
		int i;
		int nb;
		i = 0;
		nb = 0;
		while (str[i] != '\0')
		{
				if (str[i] != c)
						nb++;
				while (str[i] != c && str[i] != '\0')
						i++;
				while (str[i] == c)
						i++;
		}
		return (nb);
}

char **ft_split2(char *str, char *c, int i)
{
		int j;
		int word;
		char **tab;
		j = 0;
		word = nb_word(str, c[0]);
		if (!(tab = malloc(sizeof(char *) * (word + 1))))
				return (NULL);
		while (!(word = 0) && str[i] == c[0])
				i++;
		while (str[i] != '\0')
		{
				while (str[i + j] != c[0] && str[i + j] != '\0')
						j++;
				while (str[i + j] == c[0])
						j++;
				if (str[i + j - 1] == c[0])
						str[i + j - 1] = '\0';
				tab[word++] = ft_strtrim(&str[i], c);
				i = i + j;
				j = 0;
		}
		tab[word] = 0;
		return(tab);
}
char **ft_split(const char *str, char *c)
{
		char *st;
		char **tab;
		st = ft_strdup(str);
		tab = ft_split2(st, c, 0);
		free(st);
		return (tab);
}
