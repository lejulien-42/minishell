/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_helper2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 15:57:49 by lejulien          #+#    #+#             */
/*   Updated: 2020/12/06 14:23:52 by lejulien         ###   ########.fr       */
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

static int
	ft_exit_too_args()
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

	if (ft_strncmp(node->ar->arg, "exit",
		ft_strlen(node->ar->arg)) == 0)
	{
		if (node->ar->next)
		{
			if (node->ar->next->next && is_num(node->ar->next->arg))
				return (ft_exit_too_args());
			else
			{
				if (!is_num(node->ar->next->arg))
				{
					tmp = ft_strjoin("\e[95mminichill\e[92m: exit: \e[39m",
									node->ar->next->arg);
					set_env("?", ft_strjoin(tmp,": numeric argument required\n")
									, 0, shell->envp);
					free(tmp);
				}
				else
					set_env("?", node->ar->next->arg, 0, shell->envp);
			}
		}
		shell->is_active = 0;
		return (1);
	}
	else if (ft_strncmp(node->ar->arg, "unset",
		ft_strlen(node->ar->arg)) == 0)
	{
		unset(shell, node);
		return (1);
	}
	else if (ft_strncmp(node->ar->arg, "cd",
		ft_strlen(node->ar->arg)) == 0)
	{
		cd(shell, node);
		return (1);
	}
	return (0);
}
