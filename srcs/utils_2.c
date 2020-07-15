/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 17:23:11 by lejulien          #+#    #+#             */
/*   Updated: 2020/07/14 21:50:35 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** 	These functions are used to manage the chaned list of chars
*/

void
	ft_lstclear(t_entry **lst)
{
	t_entry	*tmp;
	t_entry	*nxt;

	if (!*lst)
		return ;
	tmp = *lst;
	while (tmp != NULL)
	{
		nxt = tmp->next;
		tmp->c = 0;
		free(tmp);
		tmp = nxt;
	}
	*lst = NULL;
}

t_entry
	*add_entry(t_entry *prev_entry, char c)
{
	t_entry	*new_entry;
	t_entry	*ptr;

	if (!(new_entry = malloc(sizeof(t_entry))))
		return (NULL);
	new_entry->c = c;
	new_entry->next = NULL;
	if (!prev_entry)
		return (new_entry);
	ptr = prev_entry;
	while (ptr->next != NULL)
		ptr = ptr->next;
	ptr->next = new_entry;
	return (prev_entry);
}
