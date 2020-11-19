/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <lejulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 02:48:26 by lejulien          #+#    #+#             */
/*   Updated: 2020/11/19 15:44:32 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void
	cd2(int i, t_shell *shell, t_arg *ptr)
{
	char	buffer[500];

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

void
	cd(t_shell *shell, t_parse *node)
{
	t_arg	*ptr;
	int		i;

	i = 0;
	ptr = node->ar;
	while (ptr->next != NULL)
	{
		i++;
		ptr = ptr->next;
	}
	if (node->ar->next)
	{
		ptr = node->ar->next;
		if (ptr->arg[0] == '~')
			ptr->arg = ft_strjoin(get_env_val("HOME", shell->envp),
			&ptr->arg[1]);
		cd2(1, shell, ptr);
	}
	else
		chdir(get_env_val("HOME", shell->envp));
}
