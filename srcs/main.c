/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/05 18:50:15 by lejulien          #+#    #+#             */
/*   Updated: 2020/07/05 22:38:22 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "../includes/minishell.h"

void
	ft_putstr(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		write(1, &str[i], 1);
		i++;
	}
}

static void	ft_putchar(char c, int fd)
{
	write(fd, &c, 1);
}

void
	ft_strcpy(char *dest, char *src)
{
	int i;

	i = 0;
	if (!src || !dest)
		return;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

void		ft_putnbr_fd(int nb, int fd)
{
	unsigned int dnb;

	if (nb < 0)
	{
		ft_putchar('-', fd);
		dnb = nb * (-1);
	}
	else
		dnb = nb;
	if (dnb >= 10)
	{
		ft_putnbr_fd(dnb / 10, fd);
		ft_putchar(dnb % 10 + '0', fd);
	}
	else
		ft_putchar(dnb + '0', fd);
}

t_shell
	*init_shell()
{
	t_shell	*shell = malloc(sizeof(t_shell));
	
	ft_strcpy(shell->prefix, "minichill $ ");
	shell->is_active = 1;

	return (shell);
}

void
	ft_printf_entry(t_entry *entry)
{
	while (entry->next != NULL)
	{
		write(1, &entry->c, 1);
		entry = entry->next;
	}
	write(1, &entry->c, 1);
}

void	ft_lstclear(t_entry **lst)
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

int
	lst_str_cmp(t_entry	*entry, char *str)
{
	int i = 0;

	while (str[i] != 0 && entry->next != 0)
	{
		if (str[i] != entry->c)
			return (0);
		i++;
		entry = entry->next;
	}
	if (str[i] != entry->c)
		return (0);
	return (1);
}
	
t_entry
	*add_entry(t_entry *prev_entry, char c)
{
	t_entry *new_entry = malloc(sizeof(t_entry));
	t_entry	*ptr;

	new_entry->c = c;
	new_entry->next = NULL;
	if (!prev_entry)
		return (new_entry);
	else
	{
		ptr = prev_entry;
		while (ptr->next != NULL)
			ptr = ptr->next;
		ptr->next = new_entry;
	}
	return (prev_entry);
}

int
	main(void)
{
	char buffer[2];
	int i = 0;
	t_entry	*entry = NULL;
	buffer[1] = '\0';
	t_shell	*shell = init_shell();
	ft_putstr(shell->prefix);
	while (shell->is_active)
	{
		read(0, buffer, 1);
		if (buffer[0] == '\n')
		{
			// free the entry
			if (lst_str_cmp(entry, "exit") == 1)
				shell->is_active = 0;
			ft_lstclear(&entry);
			//free_entry(entry);
			if (shell->is_active)
				ft_putstr(shell->prefix);
		}
		else
		{
			if (i >= 0)
			{
				entry = add_entry(entry, buffer[0]);
			}
		}
		i++;
	}
	return (0);
}
