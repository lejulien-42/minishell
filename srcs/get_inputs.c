/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_inputs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 16:06:00 by lejulien          #+#    #+#             */
/*   Updated: 2020/11/19 16:09:06 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void
	get_inputs2(int *i, int is_entry, t_shell *shell, t_entry *entry)
{
	is_entry = 0;
	if (*i > 0)
		parse_and_clear(&entry, shell);
	if (shell->is_active)
	{
		if (get_env_val("PS1", shell->envp) != NULL)
			ft_putstr(get_env_val("PS1", shell->envp));
	}
	else
		ft_putstr("exit\n");
	*i = 0;
}
