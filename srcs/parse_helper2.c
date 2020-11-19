/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_helper2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 15:57:49 by lejulien          #+#    #+#             */
/*   Updated: 2020/11/19 16:02:51 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int
	do_built_in(t_parse *node, t_shell *shell)
{
	if (ft_strncmp(node->ar->arg, "exit",
		ft_strlen(node->ar->arg)) == 0)
	{
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
