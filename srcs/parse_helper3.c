/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_helper3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 23:00:13 by lejulien          #+#    #+#             */
/*   Updated: 2020/12/14 13:35:56 by lejulien         ###   ########.fr       */
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
				set_env("?", ft_strjoin(tmp, ": numeric argument required\n")
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

int
	check_pipe_null(t_parse *node, t_parse *res)
{
	if (node->ar == NULL)
	{
		if (node->sep && ft_strncmp(node->sep, "|", ft_strlen(node->sep)) == 0)
		{
			ft_putstr("\e[95mminichill\e[92m: ");
			ft_putstr("\e[39msyntax error near unexpected token '|'\n");
		}
		ft_free_parse(res);
		return (1);
	}
	return (0);
}
