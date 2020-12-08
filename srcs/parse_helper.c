/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 18:39:46 by lejulien          #+#    #+#             */
/*   Updated: 2020/12/08 18:27:15 by frtalleu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>

extern int	g_isex;

int
	check_first_arg(char *entry, char *presumed_entry)
{
	int	i;

	i = 0;
	while (entry[i] != '\0' && presumed_entry[i] != '\0')
	{
		if (entry[i] != presumed_entry[i])
			return (0);
		i++;
	}
	if (entry[i] != presumed_entry[i])
		return (0);
	return (1);
}

t_parse
	*db_lst(t_parse *res)
{
	t_parse *node;
	t_parse *ret;

	ret = res;
	while (ret->next != NULL)
	{
		node = ret;
		ret = node->next;
		ret->prev = node;
	}
	ret->prev = node;
	res->prev = NULL;
	return (res);
}

void
	ft_free_parse(t_parse *node)
{
	t_arg	*arr;
	t_parse	*temp;

	while (node != NULL)
	{
		if (node->ar != NULL)
		{
			while (node->ar != NULL)
			{
				arr = node->ar;
				free(arr->arg);
				node->ar = arr->next;
				free(arr);
			}
		}
		free(node->sep);
		temp = node->next;
		free(node);
		node = temp;
	}
}

int
	print_pipe_error(t_parse *node)
{
	if (node->ar == NULL)
	{
		if (node->sep && ft_strncmp(node->sep, "|", ft_strlen(node->sep)) == 0)
		{
			ft_putstr("\e[95mminichill\e[92m: \e[39msyntax");
			ft_putstr(" error near unexpected token '|'\n");
		}
		return (1);
	}
	return (0);
}

void
	entry_checker(char *str, t_shell *shell)
{
	t_parse *res;
	t_parse *node;

	res = db_lst(parser(str, shell));
	node = res;

	while (node != NULL)
	{
		if (print_pipe_error(node) == 1)
			return (ft_free_parse(res));
		if (node->ar->arg)
		{
			g_isex = 1;
			if (!(do_built_in(node, shell)) &&
			!(is_prog(node->ar->arg, shell, node)))
			{
				set_env("?", "127", 0, shell->envp);
				ft_wrong(node->ar->arg);
			}
			g_isex = 0;
		}
		node = node->next;
	}
	ft_free_parse(res);
}
