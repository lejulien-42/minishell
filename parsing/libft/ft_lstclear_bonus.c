/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frtalleu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 02:33:11 by frtalleu          #+#    #+#             */
/*   Updated: 2019/11/14 07:01:13 by frtalleu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list *here;
	t_list *after;

	if (!del || !*lst)
		return ;
	here = *lst;
	while (here != NULL)
	{
		after = here->next;
		del(here->content);
		free(here);
		here = after;
	}
	*lst = NULL;
}
