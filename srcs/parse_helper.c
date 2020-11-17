/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 18:39:46 by lejulien          #+#    #+#             */
/*   Updated: 2020/11/17 16:39:05 by frtalleu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>

int g_ctrl_c;

/*
** These functions are for the parsing
*/

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

/*
**	The function bellow handle the parsing
**	It has the entry in a string and shell 
*/

void parse_tester(t_parse *res)
{
	t_arg *aa;
	t_parse *node;
	int i = 0;
	
	node = res;
	aa = res->ar;
	while (node != NULL)
	{
		while (aa != NULL)
		{
			printf("arg %i => %s\n", i, aa->arg);
			aa = aa->next;
			i++;
		}
		i = 0;
		printf("sep =>%s\n", node->sep);
		node = node->next;
		if (node != NULL)
			aa = node->ar;
	}
}

t_parse *db_lst(t_parse *res)
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

void ft_free_parse(t_parse *node)
{
	t_arg *arr;
	t_parse *temp;

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
		temp = node->next;
		free(node);
		node = temp;
	}
}


void
	entry_checker(char *str, t_shell *shell)
{
	t_parse *res;
	t_parse *node;

	res = db_lst(parser(str, shell));
	//res = parser(str, shell);
	//parse_tester(res);
	node = res;
	while (node != NULL)
	{
		if (node->ar == NULL)
			return ;
		if (node->ar->arg)
		{
			if (ft_strncmp(node->ar->arg, "exit",
				ft_strlen(node->ar->arg)) == 0)
				shell->is_active = 0;
			else if (ft_strncmp(node->ar->arg, "unset",
				ft_strlen(node->ar->arg)) == 0)
				unset(shell, node);
			else if (ft_strncmp(node->ar->arg, "cd",
				ft_strlen(node->ar->arg)) == 0)
				cd(shell, node);
			else if (is_prog(node->ar->arg, shell, node))
			{
			}
			else
				ft_wrong(node->ar->arg);
		}
		node = node->next;
	}
	ft_free_parse(res);
}
