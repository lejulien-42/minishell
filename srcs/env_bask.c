/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_bask.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <lejulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 17:59:26 by lejulien          #+#    #+#             */
/*   Updated: 2020/11/19 15:36:18 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int
	lst_len(t_envars *env)
{
	t_envars	*ptr;
	int			i;

	ptr = env;
	i = 0;
	while (ptr != NULL)
	{
		ptr = ptr->next;
		i++;
	}
	return (i);
}

int
	av_len(t_arg *env)
{
	t_arg	*ptr;
	int		i;

	ptr = env;
	i = 0;
	while (ptr != NULL)
	{
		ptr = ptr->next;
		i++;
	}
	return (i);
}

char
	**ft_env_back(t_envars **envp)
{
	char		**env;
	int			i;
	char		*equal;
	t_envars	*ptr;
	char		*env_line;

	i = 0;
	ptr = *envp;
	if (!(env = malloc((lst_len(*envp) + 1) * sizeof(char *))))
		return (NULL);
	while (i < lst_len(*envp))
	{
		equal = ft_strjoin(ptr->name, "=");
		env_line = ft_strjoin(equal, ptr->value);
		free(equal);
		env[i] = ft_strdup(env_line);
		free(env_line);
		i++;
		ptr = ptr->next;
	}
	env[i] = NULL;
	return (env);
}

char
	**ft_get_av(t_arg *arg)
{
	t_arg	*ptr;
	char	**av;
	int		i;

	i = 0;
	ptr = arg;
	i = 0;
	if (!(av = malloc((av_len(arg) + 1) * sizeof(char *))))
		return (NULL);
	while (i < av_len(arg))
	{
		av[i] = ft_strdup(ptr->arg);
		i++;
		ptr = ptr->next;
	}
	av[i] = NULL;
	return (av);
}

void
	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}
