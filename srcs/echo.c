/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <lejulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/04 18:05:28 by lejulien          #+#    #+#             */
/*   Updated: 2020/09/04 18:39:04 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void
	ft_echo_two(int i, int *is_n)
{
	if (i > 0 && !*is_n)
		ft_putstr(" ");
	if (i > 1 && *is_n)
		ft_putstr(" ");
}

static void
	ft_echo_three(char *str, int i, int *is_n)
{
	if (i != 0)
	{
		ft_echo_two(i, is_n);
		ft_putstr(str);
	}
	else
	{
		if (ft_strncmp(str, "-n", ft_strlen(str)) == 0)
			*is_n = 1;
		else
			ft_putstr(str);
	}
}

void
	ft_echo(t_shell *shell, t_parse *node)
{
	t_arg	*ptr;
	int		i;
	int		is_n;

	i = 0;
	is_n = 0;
	ptr = node->ar->next;
	if (ptr == NULL)
		ft_putstr("\n");
	else
	{
		while (ptr != NULL)
		{
			ft_echo_three(ptr->arg, i, &is_n);
			ptr = ptr->next;
			i++;
		}
		if (!is_n)
			ft_putstr("\n");
	}
}
