/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 16:58:25 by lejulien          #+#    #+#             */
/*   Updated: 2020/07/22 11:33:41 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
**	display all environment vars
*/

void
	get_env(char ***envp)
{
	int i;

	i = 0;
	while (envp[0][i])
	{
		ft_putstr(envp[0][i]);
		ft_putstr("\n");
		i++;
	}
}

/*
**	if str is the name of an env var, return 1
**
**	if var non-existant return -1
*/

int
	check_env(char *str, char ***envp)
{
	int i;
	int j;

	i = 0;
	while (envp[0][i])
	{
		if (ft_strncmp(str, envp[0][i], ft_strlen(str)) == 0)
		{
			j = 0;
			while (envp[0][i][j] != '=' && envp[0][i][j] != '\0')
				j++;
			j++;
			ft_putstr(&envp[0][i][j]); // Pour le debug
			return (1);
		}
		i++;
	}
	return (0);
}
