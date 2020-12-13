/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_helper3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 23:00:13 by lejulien          #+#    #+#             */
/*   Updated: 2020/12/13 23:02:56 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int
	check_num_arg(t_parse *node, char *tmp, t_shell *shell)
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
