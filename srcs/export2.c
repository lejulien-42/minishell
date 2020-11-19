/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 15:50:12 by lejulien          #+#    #+#             */
/*   Updated: 2020/11/19 15:56:01 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void
	export_env2(char *name, t_arg *ptr, t_shell *shell, int i)
{
	if (ft_strlen(ptr->arg) > len_equal(ptr->arg))
		set_env(name, &ptr->arg[i], 1, shell->envp);
	else if (ptr->next != NULL)
		set_if_next_arg(name, ptr, shell);
	else
		set_env(name, "\0", 1, shell->envp);
}
