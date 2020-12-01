/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frtalleu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 19:01:03 by frtalleu          #+#    #+#             */
/*   Updated: 2020/12/01 11:44:59 by frtalleu         ###   ########.fr       */
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

int		solve_norme_shit(char *str)
{
	int i;

	i = 0;
	if ((str[i] == '"' || str[i] == '\'') &&
	(str[i + 1] == str[i] || str[i + 1] == '\0'))
		return (1);
	return (0);
}

t_parse	*parser(char *str, t_shell *shell)
{
	t_parse	*res;
	int		i;

	i = 0;
	res = init_struct_parse();
	while (str[i] != '\0' && is_sep(str[i]) == 0)
	{
		if (solve_norme_shit(&str[i]) == 1 && str[i + 1] != '\0')
			i = i + 2;
		else if (solve_norme_shit(&str[i]) == 1 && str[++i] == '\0')
			break ;
		else if (str[i] != ' ' && is_sep(str[i]) == 0 && str[i] != '\0')
		{
			res = take_arg(&str[i], res, shell);
			i = i + size_arg(&str[i]);
			if ((ft_strncmp(res->ar->arg, "export", 6)) == 0)
				export_env(shell, res, 0);
		}
		else if (!(is_sep(str[++i]) == 0))
			break ;
	}
	if (is_sep(str[i]) == 1)
		res->next = parser(&str[i + cp_sep(&str[i], &res->sep)], shell);
	return (res);
}
