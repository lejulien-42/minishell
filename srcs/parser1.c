/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frtalleu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/09 11:30:43 by frtalleu          #+#    #+#             */
/*   Updated: 2020/12/01 11:21:10 by frtalleu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "../includes/minishell.h"

int		is_sep(char c)
{
	if (c == '<' || c == '>' || c == ';' || c == '|')
		return (1);
	return (0);
}

int		cp_sep(char *str, char **to_fill)
{
	int		i;
	char	*st;

	i = 0;
	while (is_sep(str[i]) == 1)
		i++;
	if (!(st = malloc(sizeof(char) * (i + 1))))
		return (0);
	i = 0;
	while (is_sep(str[i]) == 1)
	{
		st[i] = str[i];
		i++;
	}
	st[i] = '\0';
	*to_fill = st;
	return (i);
}

t_parse	*init_struct_parse(void)
{
	t_parse *res;

	if (!(res = malloc(sizeof(t_parse))))
		return (NULL);
	res->sep = NULL;
	res->ar = NULL;
	res->is_next_pipe = 0;
	res->fd = 0;
	res->next = NULL;
	res->prev = NULL;
	return (res);
}

t_arg	*init_arg(void)
{
	t_arg *res;

	if (!(res = malloc(sizeof(t_arg))))
		return (NULL);
	res->arg = NULL;
	res->next = NULL;
	return (res);
}

t_arg	*add_arg(t_arg *dest, t_arg *src)
{
	t_arg *node;

	if (dest == NULL)
		return (src);
	node = dest;
	while (node->next != NULL)
		node = node->next;
	node->next = src;
	return (dest);
}
