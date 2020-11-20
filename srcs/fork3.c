/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 14:46:08 by lejulien          #+#    #+#             */
/*   Updated: 2020/11/20 14:49:05 by lejulien         ###   ########.fr       */
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
