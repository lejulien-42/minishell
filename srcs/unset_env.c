/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <lejulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 22:20:57 by lejulien          #+#    #+#             */
/*   Updated: 2020/07/25 22:27:48 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void
	free_env(t_envars *env)
{
	free(env->name);
	free(env->value);
	free(env);
}

static void
	unset_last(t_envars *ptr, t_envars *ptr2, char *name)
{
	if (ft_strncmp(ptr->name, name, ft_strlen(name)) == 0)
	{
		ptr2->next = NULL;
		free_env(ptr);
	}
}

void
	unset_env(char *name, t_envars **envp)
{
	t_envars	*ptr;
	t_envars	*ptr2;

	ptr = *envp;
	ptr2 = *envp;
	if (ft_strncmp(ptr->name, name, ft_strlen(name)) == 0)
	{
		*envp = ptr->next;
		free_env(ptr2);
		return ;
	}
	while (ptr->next != NULL)
	{
		ptr = ptr->next;
		if (ft_strncmp(ptr->name, name, ft_strlen(name)) == 0)
		{
			ptr2->next = ptr->next;
			free_env(ptr);
			return ;
		}
		if (ptr->next != NULL)
			ptr2 = ptr2->next;
	}
	unset_last(ptr, ptr2, name);
}
