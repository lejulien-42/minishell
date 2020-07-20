/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frtalleu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 03:30:03 by frtalleu          #+#    #+#             */
/*   Updated: 2019/11/14 03:49:28 by frtalleu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft.h"

static int		is_in_base(const char c, const char *base)
{
	int i;

	i = 0;
	while (base[i] != '\0')
	{
		if (base[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int		ft_length(const char *start, const char *end)
{
	int i;

	i = 0;
	while (start != end)
	{
		i++;
		start++;
	}
	return (i);
}

char			*ft_strtrim(char const *s1, char const *set)
{
	char const	*start;
	char const	*end;
	char		*str;
	int			i;

	if (!s1)
		return (0);
	start = s1;
	if (!set)
		return (ft_strdup(s1));
	while (is_in_base(*start, set) != 0 && start != '\0')
		start++;
	if (*start == '\0')
		return (ft_strdup(""));
	while (*s1 != '\0')
		s1++;
	s1--;
	end = s1;
	while (is_in_base(*end, set) != 0)
		end--;
	i = ft_length(start, end);
	if (!(str = ft_calloc(i + 2, sizeof(char))))
		return (NULL);
	str = ft_memcpy(str, start, i + 1);
	return (str);
}
