/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frtalleu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/09 11:34:44 by frtalleu          #+#    #+#             */
/*   Updated: 2020/12/01 11:42:43 by frtalleu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "../includes/minishell.h"

int	backslash_dc(char c)
{
	if (c == '$' || c == '`' || c == '"' || c == '\\')
		return (1);
	return (0);
}

int	backslash_wc(char c)
{
	return (1);
}

int	fill_simple(char **dest, char *src)
{
	int		i;
	char	*tmp;

	i = 0;
	while (src[i] != '$' && src[i] != '\0' && src[i] != '"')
		i++;
	tmp = ft_strndup(src, i);
	*dest = tmp;
	return (i);
}

int	fill_dollar(char **dest, char *src, t_shell *shell)
{
	int		i;
	char	*tmp;
	char	*tp;

	i = 1;
	while (src[i] != '$' && src[i] != '\0')
		i++;
	tmp = ft_strndup(&src[1], i - 1);
	tp = ft_strdup(get_env_val(tmp, shell->envp));
	free(tmp);
	*dest = tp;
	return (i);
}

int	fill_backslash(char **dest, char *src, int (*f)(char))
{
	char	*tmp;

	if (f(src[0]) == 0)
	{
		if (!(tmp = malloc(sizeof(char) * 3)))
			return (0);
		tmp[0] = src[0];
		tmp[1] = src[1];
		tmp[2] = '\0';
	}
	else
	{
		if (!(tmp = malloc(sizeof(char) * 2)))
			return (0);
		tmp[0] = src[1];
		tmp[1] = '\0';
	}
	*dest = tmp;
	return (2);
}
