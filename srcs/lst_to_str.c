/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_to_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 16:09:30 by lejulien          #+#    #+#             */
/*   Updated: 2020/08/11 12:22:57 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** This functions create a string mallocked from a chained list of chars
*/

t_entry
	*lst_skip_white_space(t_entry *entry)
{
	while ((entry->c == '\v' || entry->c == '\r' || entry->c == '\n' ||
			entry->c == '\t' || entry->c == '\f' || entry->c == ' ') &&
				entry->next != NULL)
		entry = entry->next;
	return (entry);
}

char
	*lst_to_str(t_entry *entry)
{
	t_entry	*ptr;
	int		i;
	char	*str;

	i = 0;
	ptr = entry;
	ptr = lst_skip_white_space(ptr);
	while (ptr->next != NULL)
	{
		i++;
		ptr = ptr->next;
	}
	if (!(str = malloc(i * sizeof(char) + 2)))
		return (NULL);
	i = 0;
	entry = lst_skip_white_space(entry);
	while (entry->next != NULL)
	{
		str[i] = entry->c;
		i++;
		entry = entry->next;
	}
	str[i] = entry->c;
	str[i + 1] = '\0';
	return (str);
}
