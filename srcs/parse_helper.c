/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 18:39:46 by lejulien          #+#    #+#             */
/*   Updated: 2020/07/14 18:39:53 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** These functions are for the parsing
*/

int
	check_first_arg(char *entry, char *presumed_entry)
{
	int	i;

	i = 0;
	while (entry[i] != '\0' && presumed_entry[i] != '\0')
	{
		if (entry[i] != presumed_entry[i])
			return (0);
		i++;
	}
	if (entry[i] != presumed_entry[i])
		return (0);
	return (1);
}

/*
**	The function bellow handle the parsing
*/

void
	entry_checker(char *str, t_shell *shell)
{
	if (check_first_arg(str, "exit"))
		shell->is_active = 0;
	else if (check_first_arg(str, "leaks"))
		system("leaks minishell");
	else if (check_first_arg(str, "pwd"))
		get_pwd();
	else if (check_first_arg(str, "make coffee"))
		ft_putstr("Here is your coffee : ☕️\n");
	else
		ft_wrong(str);
}

void
	parse_entry(t_entry *entry, t_shell *shell)
{
	char	*str;

	str = lst_to_str(entry);
	if (!ft_is_space(str))
		entry_checker(str, shell);
	free(str);
	ft_lstclear(&entry);
}
