/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 10:14:33 by lejulien          #+#    #+#             */
/*   Updated: 2020/07/22 11:43:25 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int
	ft_put_env(char *str, t_shell *shell)
{
	char *buffer;

	if (str[0] == '\0')
		return (0);
	return (check_env(str, shell->envp));
}

void
	ft_echo(t_shell *shell, t_parse *node)
{
	int is_n;
	int is_entry;

	is_n = 0;
	if (node->flag != NULL)
	{
		if (ft_strncmp(node->flag, "n", ft_strlen(node->flag)) == 0)
			is_n = 1;
	}
	while (node->arg != NULL)
	{
		is_entry = 1;
		if (node->arg->argu != NULL)
		{
			if (node->arg->argu[0] == '$')
				is_entry = ft_put_env(&node->arg->argu[1], shell);
			else
				ft_putstr(node->arg->argu);
			if (is_entry)
				ft_putstr(" ");
		}
		node->arg = node->arg->next;
	}
	if (is_n == 0)
		ft_putstr("\n");
}
