/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 16:57:24 by lejulien          #+#    #+#             */
/*   Updated: 2020/11/19 16:59:09 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void
	check_redirect2(t_parse *node)
{
	if (node->next && node->next->ar->arg)
	{
		node->fd = open(node->next->ar->arg, O_RDONLY);
		if (node->fd == -1)
		{
			ft_putstr("minishell: ");
			ft_putstr(node->next->ar->arg);
			ft_putstr(": No such file or directory\n");
		}
		else
			dup2(node->fd, 0);
	}
}
