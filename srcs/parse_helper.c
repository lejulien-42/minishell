/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 18:39:46 by lejulien          #+#    #+#             */
/*   Updated: 2020/07/29 18:27:30 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

void
	entry_checker(char *str, t_shell *shell)
{
	t_parse *res;
	t_parse *node;

	res = parser(str);
	node = res;
	while (node != NULL)
	{
		if (ft_strncmp(node->cmd, "exit", ft_strlen(node->cmd)) == 0)
			shell->is_active = 0;
		else if (ft_strncmp(node->cmd, "leaks", ft_strlen(node->cmd)) == 0)
			system("leaks minishell");
		else if (ft_strncmp(node->cmd, "pwd", ft_strlen(node->cmd)) == 0)
			get_pwd();
		else if (ft_strncmp(node->cmd, "makeCoffee",
				ft_strlen(node->cmd)) == 0)
			ft_putstr("Here is your coffee : ☕️\n");
		else if (ft_strncmp(node->cmd, "lambda", ft_strlen(node->cmd)) == 0)
			set_env("PS1", "\e[91mHalf-Life λ \e[39m", 1, shell->envp);
		else if (ft_strncmp(node->cmd, "env", ft_strlen(node->cmd)) == 0)
			ft_print_env(*shell->envp);
		else if (ft_strncmp(node->cmd, "unset", ft_strlen(node->cmd)) == 0)
			unset(shell, node);
		else if (ft_strncmp(node->cmd, "export", ft_strlen(node->cmd)) == 0)
			export_env(shell, node);
		else if (is_prog(node->cmd, shell, node))
		{
		}
		else
			ft_wrong(node->cmd);
		node = node->next;
	}
	ft_free_parse(res);
}
