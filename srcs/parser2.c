/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frtalleu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 16:46:26 by frtalleu          #+#    #+#             */
/*   Updated: 2020/07/25 16:09:16 by frtalleu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "stdio.h"

void	ft_free_parse(t_parse *res)
{
	t_parse *node;

	node = res;
	while(node != NULL)
	{
		free(res->cmd);
		free(res->flag);
		free(res->sep);
		ft_free_arg(res->arg);
		node = res->next;
		free(res);
		res = node;
	}
}

int	is_sep(char *str)
{
	if (str[0] != '<' && str[0] != '>' && str[0] != '|' && str[0] != ';')
		return (1);
	return (0);
}

int	cp_until_space(char *str, char **to_fill)
{
	int		i;
	char	*st;

	i = 0;
	while (str[i] != ' ' && str[i] != '\0' && is_sep(&str[i]) == 1)
		i++;
	if (!(st = malloc(sizeof(char) * (i + 1))))
		return (0);
	i = 0;
	while (str[i] != ' ' && str[i] != '\0' && is_sep(&str[i]) == 1)
	{
		st[i] = str[i];
		i++;
	}
	st[i] = '\0';
	*to_fill = st;
	return (i);
}

int	cp_sep(char *str, char **to_fill)
{
	int		i;
	char	*st;

	i = 0;
	while (is_sep(&str[i]) == 0)
		i++;
	if (!(st = malloc(sizeof(char) * (i + 1))))
		return (0);
	i = 0;
	while (is_sep(&str[i]) == 0)
	{
		st[i] = str[i];
		i++;
	}
	st[i] = '\0';
	*to_fill = st;
	return (i);
}

int	cp_until_cote(char *str, char **to_fill)
{
	int		i;
	char	*st;

	i = 1;
	while (str[i] != str[0] && str[i] != '\0')
		i++;
	if (!(st = malloc(sizeof(char) * i)))
		return (0);
	i = 1;
	while (str[i] != str[0] && str[i] != '\0')
	{
		st[i - 1] = str[i];
		i++;
	}
	st[i - 1] = '\0';
	*to_fill = st;
	return (i);
}
