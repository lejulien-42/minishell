/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 16:57:24 by lejulien          #+#    #+#             */
/*   Updated: 2020/12/10 18:50:45 by lejulien         ###   ########.fr       */
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
			ft_putstr(": No such file or directory");
		}
		else
			dup2(node->fd, 0);
	}
}

void
	check_redirect3(t_parse *node)
{
	if (node->next && node->next->ar->arg)
	{
		node->fd = open(node->next->ar->arg, O_RDONLY);
		if (node->fd == -1)
		{
			ft_putstr("minishell: ");
			ft_putstr(node->next->ar->arg);
			ft_putstr(": No such file or directory");
		}
	}
}

void
	red_file(t_parse *ptr)
{
	if (ft_strncmp(ptr->sep, ">", ft_strlen(ptr->sep)) == 0)
	{
		if (ptr->next && ptr->next->ar->arg)
		{
			ptr->fd = open(ptr->next->ar->arg, O_CREAT | O_RDWR |
						O_TRUNC, 0664);
		}
	}
	if (ft_strncmp(ptr->sep, "<", ft_strlen(ptr->sep)) == 0)
		check_redirect3(ptr);
	if (ft_strncmp(ptr->sep, ">>", ft_strlen(ptr->sep)) == 0)
	{
		if (ptr->next && ptr->next->ar->arg)
		{
			ptr->fd = open(ptr->next->ar->arg, O_CREAT | O_APPEND |
							O_WRONLY, 0664);
		}
	}
}

void
	red_dup(t_parse *ptr)
{
	if (ft_strncmp(ptr->sep, ">", ft_strlen(ptr->sep)) == 0)
	{
		if (ptr->next && ptr->next->ar->arg)
		{
			ptr->fd = open(ptr->next->ar->arg, O_CREAT | O_RDWR |
							O_TRUNC, 0664);
			dup2(ptr->fd, 1);
		}
	}
	if (ft_strncmp(ptr->sep, "<", ft_strlen(ptr->sep)) == 0)
		check_redirect2(ptr);
	if (ft_strncmp(ptr->sep, ">>", ft_strlen(ptr->sep)) == 0)
	{
		if (ptr->next && ptr->next->ar->arg)
		{
			ptr->fd = open(ptr->next->ar->arg, O_CREAT | O_APPEND |
							O_WRONLY, 0664);
			dup2(ptr->fd, 1);
		}
	}
}

void
	red_dup2(t_parse *ptr)
{
	if (ft_strncmp(ptr->prev->sep, ">", ft_strlen(ptr->prev->sep)) == 0)
	{
		if (ptr && ptr->ar->arg)
		{
			ptr->prev->fd = open(ptr->ar->arg, O_CREAT | O_RDWR |
			O_TRUNC, 0664);
			dup2(ptr->prev->fd, 1);
		}
	}
	if (ft_strncmp(ptr->prev->sep, "<", ft_strlen(ptr->prev->sep)) == 0)
		check_redirect2(ptr->prev);
	if (ft_strncmp(ptr->prev->sep, ">>", ft_strlen(ptr->prev->sep)) == 0)
	{
		if (ptr && ptr->ar->arg)
		{
			ptr->prev->fd = open(ptr->ar->arg, O_CREAT | O_APPEND |
							O_WRONLY, 0664);
			dup2(ptr->prev->fd, 1);
		}
	}
}
