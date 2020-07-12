/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/12 21:55:10 by lejulien          #+#    #+#             */
/*   Updated: 2020/07/12 22:21:43 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Permet d'afficher le repertoire courant
*/

void
	get_pwd(void)
{
	char str[60];

	getcwd(str, 60);
	ft_putstr(str);
	ft_putstr("\n");
}

/*
** Permet de checker si une string est remplie d'espaces
*/

int
	ft_is_space(char *str)
{
	int i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\f' ||
		str[i] == '\n' || str[i] == '\r' || str[i] == '\v')
		i++;
	if (str[i] == '\0')
		return (1);
	else
		return (0);
}

/*
** Take the entry and write command not found
*/

void
	ft_wrong(char *str)
{
	int i;

	i = 0;
	if (!ft_is_space(str))
	{
		ft_putstr("minishell: ");
		while (str[i] == ' ' || str[i] == '\t' || str[i] == '\f' ||
			str[i] == '\n' || str[i] == '\r' || str[i] == '\v')
			i++;
		while (str[i] != ' ' && str[i] != '\t' && str[i] != '\f' &&
			str[i] != '\n' && str[i] != '\r' && str[i] != '\v' &&
				str[i] != '\0')
		{
			write(1, &str[i], 1);
			i++;
		}
		ft_putstr(": command not found\n");
	}
}
