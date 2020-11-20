/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <lejulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 20:03:12 by lejulien          #+#    #+#             */
/*   Updated: 2020/07/25 20:10:09 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char
	*get_env_val(char *name, t_envars **envp)
{
	t_envars	*ptr;

	ptr = *envp;
	while (ptr != NULL)
	{
		if (ft_strncmp(ptr->name, name, ft_strlen(name)) == 0)
			return (ptr->value);
		ptr = ptr->next;
	}
	return (NULL);
}
