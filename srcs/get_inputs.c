/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_inputs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 16:06:00 by lejulien          #+#    #+#             */
/*   Updated: 2020/12/14 15:48:00 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void
	get_inputs2(int *i, t_shell *shell)
{
	if (shell->is_active)
	{
		if (get_env_val("PS1", shell->envp) != NULL)
			ft_putstr(get_env_val("PS1", shell->envp));
	}
	else
		ft_putstr("exit\n");
	*i = 0;
}

void
	get_inputs3(int ret, int is_entry, t_shell *shell)
{
	if (ret == 0 && is_entry == 0)
	{
		ft_putstr("exit\n");
		shell->is_active = 0;
	}
}
