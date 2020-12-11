/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_prog.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 17:20:18 by lejulien          #+#    #+#             */
/*   Updated: 2020/12/11 15:31:28 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <sys/stat.h>
#include <sys/types.h>

int
	is_prog3(t_shell *shell, char **path, t_parse *node, char *tested)
{
	struct stat	sb;

	if (node->prev && node->prev->sep && is_seppa(node->prev->sep) && node->sep
		&& ft_strncmp(node->sep, "|", ft_strlen(node->sep)) == 0)
		execute_prog(tested, shell, node);
	if (is_exist(tested))
	{
		if (stat(tested, &sb) == 0 && (sb.st_mode & S_IXUSR))
		{
		}
		else
		{
			return (0);
		}
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

int
	execute2(t_parse *node)
{
	if (node->sep)
		check_redirect(node);
	if (node->is_next_pipe && dup2(node->pipes[1], 1) < 0)
		return (0);
	if (node->prev && node->prev->is_next_pipe == 1 &&
		dup2(node->prev->pipes[0], 0) < 0)
		return (0);
	return (1);
}
