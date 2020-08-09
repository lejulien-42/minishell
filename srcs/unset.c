/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <lejulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 03:04:39 by lejulien          #+#    #+#             */
/*   Updated: 2020/08/09 18:02:00 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void
	unset(t_shell *shell, t_parse *node)
{
	t_arg	*ptr;

	ptr = node->ar->next;
	while (ptr)
	{
		if (get_env_val(ptr->arg, shell->envp) != NULL)
			unset_env(ptr->arg, shell->envp);
		ptr = ptr->next;
	}
}
