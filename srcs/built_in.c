/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <lejulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 14:01:17 by lejulien          #+#    #+#             */
/*   Updated: 2020/11/24 14:00:59 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <errno.h>

int
	is_built_in(t_parse *node, t_shell *shell)
{
	if (ft_strncmp(node->ar->arg, "leaks", ft_strlen(node->ar->arg)) == 0)
		return (1);
	else if (ft_strncmp(node->ar->arg, "pwd", ft_strlen(node->ar->arg)) == 0)
		return (1);
	else if (ft_strncmp(node->ar->arg, "lambda", ft_strlen(node->ar->arg)) == 0)
		return (1);
	else if (ft_strncmp(node->ar->arg, "env", ft_strlen(node->ar->arg)) == 0)
		return (1);
	else if (ft_strncmp(node->ar->arg, "export", ft_strlen(node->ar->arg)) == 0)
		return (1);
	else if (ft_strncmp(node->ar->arg, "echo", ft_strlen(node->ar->arg)) == 0)
		return (1);
	return (0);
}

void
	ex_built_in(t_parse *node, t_shell *shell)
{
	if (ft_strncmp(node->ar->arg, "leaks", ft_strlen(node->ar->arg)) == 0)
		system("leaks minishell");
	else if (ft_strncmp(node->ar->arg, "pwd", ft_strlen(node->ar->arg)) == 0)
		get_pwd(shell);
	else if (ft_strncmp(node->ar->arg, "lambda", ft_strlen(node->ar->arg)) == 0)
		set_env("PS1", "\e[91mHalf-Life λ \e[39m", 1, shell->envp);
	else if (ft_strncmp(node->ar->arg, "env", ft_strlen(node->ar->arg)) == 0)
		ft_print_env(*shell->envp);
	else if (ft_strncmp(node->ar->arg, "export", ft_strlen(node->ar->arg)) == 0)
		export_env(shell, node, 1);
	else if (ft_strncmp(node->ar->arg, "echo", ft_strlen(node->ar->arg)) == 0)
		ft_echo(shell, node);
	errno = 0;
}
