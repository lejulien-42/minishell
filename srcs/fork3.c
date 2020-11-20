/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 14:46:08 by lejulien          #+#    #+#             */
/*   Updated: 2020/11/20 15:08:29 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void
	close_pipes(int is_pipe, t_parse *node)
{
	if (is_pipe)
	{
		close(node->pipes[1]);
		if (!node->next || (node->sep &&
			ft_strncmp(node->sep, ";", ft_strlen(node->sep)) == 0))
			close(node->pipes[0]);
	}
	if (node->prev && node->prev->is_next_pipe)
		close(node->prev->pipes[0]);
}

int
	open_pipes(t_parse *node, t_exinfo *info, char *path, int *ret)
{
	if (!execute2(node))
		return (0);
	if (is_built_in(node, node->shell))
		ex_built_in(node, node->shell);
	else if (node->fd != -1 && (*ret = execve(path, info->av, info->env)) < 0)
		return (0);
	if (node->sep)
		close_redirect(node);
	return (1);
}

int
	init_fork(int *is_pipe, t_parse *node, int *pid)
{
	*is_pipe = 0;
	if (!initialize_pipe(node, is_pipe))
		return (0);
	*pid = fork();
	return (1);	
}
