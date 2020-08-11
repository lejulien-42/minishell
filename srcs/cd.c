/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <lejulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 02:48:26 by lejulien          #+#    #+#             */
/*   Updated: 2020/08/11 03:14:16 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void
	cd(t_shell *shell, t_parse *node)
{
	t_arg	*ptr;
	int		i;
	char	buffer[500];

	i = 0;
	ptr = node->ar;
	while (ptr->next != NULL)
	{
		i++;
		ptr = ptr->next;
	}
	ptr = node->ar->next;
	if (i >= 1)
	{
		if (chdir(ptr->arg) == 0)
		{
			getcwd(buffer, 500);
			set_env("PWD", buffer, 1, shell->envp);
		}
		else
		{
			ft_putstr("minishell: cd: ");
			ft_putstr(ptr->arg);
			ft_putstr(": No such file or directory\n");
		}
	}
}
