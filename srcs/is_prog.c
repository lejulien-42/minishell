/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_prog.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 17:20:18 by lejulien          #+#    #+#             */
/*   Updated: 2020/11/19 17:30:21 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int
	is_prog3(t_shell *shell, char **path, t_parse *node, char *tested)
{
	if (is_exist(tested))
	{
		execute_prog(tested, shell, node);
		free(tested);
		free_tab(path);
		return (1);
	}
	free(tested);
	return (0);
}

int
	initialize_pipe(t_parse *node, int *is_pipe)
{
	if ((node->sep && ft_strncmp(node->sep, "|", ft_strlen(node->sep)) == 0) ||
		(node->prev && node->prev->is_next_pipe))
	{
		*is_pipe = 1;
		if (node->sep && ft_strncmp(node->sep, "|", ft_strlen(node->sep)) == 0)
			node->is_next_pipe = 1;
		if (pipe(node->pipes))
			return (0);
	}
	return (1);
}
