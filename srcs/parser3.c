/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frtalleu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/09 11:49:18 by frtalleu          #+#    #+#             */
/*   Updated: 2020/12/13 13:51:51 by frtalleu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "../includes/minishell.h"

char
	*dw_cote_built(char *str, t_shell *shell, int (*f)(char))
{
	int		i;
	char	*st;
	char	*tmp;

	i = 0;
	tmp = NULL;
	while (str[i] != '\0')
	{
		if (str[i] == '\\')
			i = i + fill_backslash(&st, &str[i], f);
		else if (str[i] == '$')
			i = i + fill_dollar(&st, &str[i], shell);
		else
			i = i + fill_simple(&st, &str[i]);
		tmp = ft_strjoindf(tmp, st);
	}
	free(str);
	return (tmp);
}

int
	manage_double_cote(char **dest, char *str, t_shell *shell, int (*f)(char))
{
	int		i;
	char	*st;
	char	*tmp;

	i = 1;
	while (str[i] != '\0' && (str[i] != '"'
		|| (str[i] == '"' && str[i - 1] == '\\' &&
		(i <= 2 || str[i - 2] != '\\'))))
		i++;
	if (!(st = malloc(sizeof(char) * i)))
		return (0);
	i = 1;
	while (str[i] != '\0' && (str[i] != '"'
		|| (str[i] == '"' && str[i - 1] == '\\' &&
		(i <= 2 || str[i - 2] != '\\'))))
	{
		st[i - 1] = str[i];
		i++;
	}
	st[i - 1] = '\0';
	tmp = dw_cote_built(st, shell, f);
	*dest = tmp;
	return (i);
}

int
	manage_simple_cote(char **dest, char *str)
{
	int		i;
	char	*st;

	i = 1;
	while (str[i] != '\0' && str[i] != '\'')
		i++;
	if (!(st = malloc(sizeof(char) * i)))
		return (0);
	i = 1;
	while (str[i] != '\0' && str[i] != '\'')
	{
		st[i - 1] = str[i];
		i++;
	}
	st[i - 1] = '\0';
	*dest = st;
	return (i);
}

int
	manage_without_cote(char **dest, char *str, t_shell *shell, int (*f)(char))
{
	int		i;
	char	*st;
	char	*tmp;
	int		j;

	i = 0;
	j = manage_wc2(str);
	if (!(st = malloc(sizeof(char) * (j + 1))))
		return (0);
	while (i < j)
	{
		st[i] = str[i];
		i++;
	}
	st[i] = '\0';
	tmp = dw_cote_built(st, shell, f);
	*dest = tmp;
	return (i);
}

char
	*manage_arg(char *str, t_shell *shell)
{
	int		i;
	char	*st;
	char	*tp;

	i = 0;
	st = NULL;
	tp = NULL;
	while (str[i] != ' ' && str[i] != '\0')
	{
		if (str[i] == '\'')
			i = i + 1 + manage_simple_cote(&st, &str[i]);
		else if (str[i] == '"')
			i = i + 1 + manage_double_cote(&st, &str[i], shell, backslash_dc);
		else
			i = i + manage_without_cote(&st, &str[i], shell, backslash_wc);
		tp = ft_strjoindf(tp, st);
	}
	free(str);
	return (tp);
}
