/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <lejulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 16:37:07 by lejulien          #+#    #+#             */
/*   Updated: 2020/07/25 17:22:07 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int
	var_is_set(char *name, t_envars *envp)
{
	t_envars	*ptr;

	ptr = envp;
	while (ptr != NULL)
	{
		if (ft_strncmp(name, ptr->name, ft_strlen(name)) == 0)
			return (1);
		ptr = ptr->next;
	}
	return (0);
}

static void
	set_set_env(char *name, char *value, int visib, t_envars *envp)
{
	t_envars	*ptr;
	char		*ptr2;

	ptr = envp;
	while (ptr != NULL)
	{
		if (ft_strncmp(name, ptr->name, ft_strlen(name)) == 0)
			break ;
		ptr = ptr->next;
	}
	ft_putstr(ptr->name);
	ptr2 = ptr->value;
	free(ptr2);
	ptr->value = ft_strdup(value);
	ptr->visibility = visib;
}

void
	set_env(char *name, char *value, int visib, t_envars *envp)
{
	if (var_is_set(name, envp))
		set_set_env(name, value, visib, envp);
	else
		ft_putstr("\nnot set\n");
}
