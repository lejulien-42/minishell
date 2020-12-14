/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_helper2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 15:57:49 by lejulien          #+#    #+#             */
/*   Updated: 2020/12/14 13:29:33 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int
	is_num(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int
	ft_exit_too_args(void)
{
	ft_putstr("exit\n");
	ft_putstr("\e[95mminichill\e[92m: \e[39m");
	ft_putstr("exit: too many arguments\n");
	return (1);
}

int
	do_built_in(t_parse *node, t_shell *shell)
{
	char *tmp;

	if (ft_strncmp(node->ar->arg, "exit", ft_strlen(node->ar->arg)) == 0)
		return (check_num_arg(node, tmp, shell));
	else if (ft_strncmp(node->ar->arg, "unset", ft_strlen(node->ar->arg)) == 0)
	{
		unset(shell, node);
		return (1);
	}
	else if (ft_strncmp(node->ar->arg, "cd", ft_strlen(node->ar->arg)) == 0)
	{
		cd(shell, node);
		return (1);
	}
	return (0);
}
