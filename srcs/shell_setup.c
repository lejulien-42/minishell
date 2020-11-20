/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_setup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 18:29:02 by lejulien          #+#    #+#             */
/*   Updated: 2020/07/21 18:00:23 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
**	This function initialize the shell structure
*/

t_shell
	init_shell(void)
{
	t_shell	shell;

	ft_strcpy(shell.prefix, "\e[95mminichill\e[92m$ \e[39m");
	shell.is_active = 1;
	return (shell);
}
