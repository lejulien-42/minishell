/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 15:19:44 by lejulien          #+#    #+#             */
/*   Updated: 2020/11/17 15:22:03 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int
	ft_len_char(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != c && str[i] != '\0')
		i++;
	return (i);
}

static int
	add_var_from_str(t_envars *env, char *str)
{
	int	i;
	int j;

	if (!(env->name = malloc((ft_len_char(str, '=') + 1) * sizeof(char))))
		return (0);
	i = 0;
	while (str[i] != '=' && str[i] != '\0')
	{
		env->name[i] = str[i];
		i++;
	}
	i++;
	env->name[i] = '\0';
	if (!(env->value = malloc((ft_strlen(&str[i]) + 1) * sizeof(char))))
		return (0);
	j = 0;
	while (str[i] != '\0')
		env->value[j++] = str[i++];
	j++;
	env->value[j] = '\0';
	env->visibility = 1;
	env->next = NULL;
	return (1);
}

t_envars
	*ft_get_envp(char ***envp, t_envars *env)
{
	int			i;
	t_envars	*ptr;
	t_envars	*ptr2;

	i = 1;
	ptr2 = env;
	if (*envp && envp[0][0])
	{
		if (!add_var_from_str(env, envp[0][0]))
			return (NULL);
	}
	while (*envp && envp[0][i])
	{
		ptr = malloc(sizeof(t_envars));
		if (!add_var_from_str(ptr, envp[0][i]))
			return (NULL);
		while (ptr2->next != NULL)
			ptr2 = ptr2->next;
		ptr2->next = ptr;
		i++;
	}
	return (env);
}

void
	ft_print_env(t_envars *env)
{
	t_envars	*ptr;

	ptr = env;
	while(ptr != NULL)
	{
		if (ptr->visibility)
		{
			ft_putstr(ptr->name);
			ft_putstr("=");
			ft_putstr(ptr->value);
			ft_putstr("\n");
		}
		ptr = ptr->next;
	}
}
