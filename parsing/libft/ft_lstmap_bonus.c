/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frtalleu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 05:14:52 by frtalleu          #+#    #+#             */
/*   Updated: 2019/11/15 06:25:24 by frtalleu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list			*begin;
	t_list			*tmp;

	if (!lst || !f)
		return (NULL);
	if (!(begin = ft_lstnew(f(lst->content))))
	{
		ft_lstclear(&begin, del);
		return (NULL);
	}
	lst = lst->next;
	while (lst)
	{
		if (!(tmp = ft_lstnew(f((void *)lst->content))))
		{
			ft_lstclear(&begin, del);
			return (NULL);
		}
		ft_lstadd_back(&begin, tmp);
		lst = lst->next;
	}
	return (begin);
}
