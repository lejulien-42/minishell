/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frtalleu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 16:45:48 by frtalleu          #+#    #+#             */
/*   Updated: 2020/07/21 12:45:05 by frtalleu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "stdio.h"
#include "GNL/get_next_line.h"

t_arg	*init_arg(void)
{
	t_arg *res;

	if (!(res = malloc(sizeof(t_arg))))
		return (NULL);
	res->argu = NULL;
	res->next = NULL;
	return (res);
}

t_parse	*init_struct_parse(void)
{
	t_parse *res;

	if (!(res = malloc(sizeof(t_parse))))
		return (NULL);
	res->cmd = NULL;
	res->flag = NULL;
	res->arg = NULL;
	res->sep = NULL;
	res->next = NULL;
	return (res);
}

int		add_arg(t_parse *res, char *str)
{
	int		i;
	t_arg	*argument;
	t_arg	*argu;

	i = 0;
	argu = res->arg;
	argument = init_arg();
	if (str[i] == '"' || str[i] == '\'')
		i = i + 1 + cp_until_cote(&str[i], &argument->argu);
	else if (is_sep(&str[i]) == 1)
		i = i + cp_until_space(&str[i], &argument->argu);
	if (res->arg == NULL)
		res->arg = argument;
	else
	{
		while (argu->next != NULL)
			argu = argu->next;
		argu->next = argument;
	}
	return (i);
}

t_parse	*parser(char *str)
{
	t_parse	*res;
	int		i;

	i = 0;
	res = init_struct_parse();
	while (str[i] == ' ')
		i++;
	i = i + cp_until_space(&str[i], &res->cmd);
	while (str[i] == ' ')
		i++;
	if (str[i] == '-')
		i = i + 1 + cp_until_space(&str[i + 1], &res->flag);
	while (str[i] == ' ')
		i++;
	while (is_sep(&str[i]) == 1 && str[i] != '\0')
	{
		if (str[i] != ' ')
			i = i + add_arg(res, &str[i]);
		while (str[i] == ' ')
			i++;
	}
	if (is_sep(&str[i]) == 0)
		res->next = parser(&str[i + cp_sep(&str[i], &res->sep)]);
	return (res);
}
