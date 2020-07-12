/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/05 18:50:15 by lejulien          #+#    #+#             */
/*   Updated: 2020/07/12 22:18:35 by lejulien         ###   ########.fr       */
/*   Updated: 2020/07/06 23:06:03 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "../includes/minishell.h"
#include "../libft/libft.h"

t_shell
	*init_shell()
{
	t_shell	*shell = malloc(sizeof(t_shell));
	
	ft_strcpy(shell->prefix, "minichell $ ");

	char path[60];
	getcwd(path, 60);
	char *ptr;
	ptr = &path[ft_strlen(path) - 1];
	while (*ptr != '/')
		ptr++;
	ptr++;
	ft_strcpy(shell->prefix, "minishell$ ");
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

int check_first_arg(char *entry, char *presumed_entry)
{
	int i;
   
	i = 0;
	while(entry[i] != '\0' && presumed_entry[i] != '\0')
	{
		if (entry[i] != presumed_entry[i])
			return (0);
		i++;
	}
	return (1);
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

char
	*lst_to_str(t_entry	*entry)
{
	t_entry *ptr;
	int i;

	i = 0;
	ptr = entry;
	while ((ptr->c == '\v' || ptr->c == '\r' || ptr->c == '\n' ||
			ptr->c == '\t' || ptr->c == '\f' || ptr->c == ' ') && ptr->next != NULL)
		ptr = ptr->next;
	while (ptr->next != NULL)
	{
		i++;
		ptr = ptr->next;
	}
	char *str = malloc(i + sizeof(char) + 1);
	i = 0;
	while ((entry->c == '\v' || entry->c == '\r' || entry->c == '\n' ||
			entry->c == '\t' || entry->c == '\f' || entry->c == ' ') && entry->next != NULL)
		entry = entry->next;
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
			if (i > 0)
			{
				char *str = lst_to_str(entry);
				if (!ft_is_space(str))
				{
					if (check_first_arg(str, "exit"))
						shell->is_active = 0;
					else if (check_first_arg(str, "leaks"))
						system("leaks minishell");
					else if (check_first_arg(str, "pwd"))
						get_pwd();
					else
						ft_wrong(str);
				}
				free(str);
				ft_lstclear(&entry);
			}
			if (shell->is_active)
				ft_putstr(shell->prefix);
			else
				ft_putstr("exit\n");
			i = 0;
		}
		else
		{
			if (i >= 0)
			{
				entry = add_entry(entry, buffer[0]);
				i++;
			}
		}
	}
	return (0);
}
