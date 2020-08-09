/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frtalleu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 19:01:03 by frtalleu          #+#    #+#             */
/*   Updated: 2020/07/25 19:01:06 by frtalleu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "../includes/minishell.h"

int		size_arg(char *str)
{
	int	i;

	i = 0;
	while (str[i] != ' ' && str[i] != '\0' && is_sep(str[i]) == 0)
	{
		if (str[i] == '\'')
		{
			i++;
			while (str[i] != '\'' && str[i] != '\0')
				i++;
			i++;
		}
		else if (str[i] == '"')
		{
			i++;
			while (str[i] != '"' && str[i] != '\0')
				i++;
			i++;
		}
		else
			i++;
	}
	return (i);
}

t_parse	*take_arg(char *str, t_parse *res, t_shell *shell)
{
	t_arg	*argu;
	char	*st;

	argu = init_arg();
	st = ft_strndup(str, size_arg(str));
	argu->arg = manage_arg(st, shell);
	if (argu->arg != NULL)
		res->ar = add_arg(res->ar, argu);
	else
		free(argu);
	return (res);
}

t_parse	*parser(char *str, t_shell *shell)
{
	t_parse	*res;
	int		i;

	i = 0;
	res = init_struct_parse();
	while (str[i] != '\0' && is_sep(str[i]) == 0)
	{
		if (str[i] != ' ' && is_sep(str[i]) == 0)
		{
			res = take_arg(&str[i], res, shell);
			i = i + size_arg(&str[i]);
		}
		else if (is_sep(str[i]) == 0)
			i++;
		else
			break ;
	}
	if (is_sep(str[i]) == 1)
		res->next = parser(&str[i + cp_sep(&str[i], &res->sep)], shell);
	return (res);
}
