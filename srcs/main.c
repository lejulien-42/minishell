/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/05 18:50:15 by lejulien          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2020/07/10 04:51:27 by lejulien         ###   ########.fr       */
=======
/*   Updated: 2020/07/06 23:06:03 by lejulien         ###   ########.fr       */
>>>>>>> e0e92544ea25f4909e5d5d23f8eabdd05b43a61b
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "../includes/minishell.h"
#include "../libft/libft.h"

int
	ft_strlen(char *str)
{
	int i = 0;

	while (str[i] != '\0')
		i++;
	return (i);
}

t_shell
	*init_shell()
{
	t_shell	*shell = malloc(sizeof(t_shell));
<<<<<<< HEAD
	
	ft_strcpy(shell->prefix, "minichell $ ");
=======

	char path[60];
	getcwd(path, 60);
	char *ptr;
	ptr = &path[ft_strlen(path) - 1];
	while (*ptr != '/')
		ptr++;
	ptr++;
	ft_strcpy(shell->prefix, "minishell$ ");
>>>>>>> e0e92544ea25f4909e5d5d23f8eabdd05b43a61b
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
<<<<<<< HEAD
	*lst_to_str(t_entry	*entry)
{
	t_entry *ptr;
	char *str;
	int i;

	i = 0;
	ptr = entry;
	while (ptr->c == '\v' || ptr->c == '\r' || ptr->c == '\n' ||
			ptr->c == '\t' || ptr->c == '\f' || ptr->c == ' ')
		ptr = ptr->next;
	while (ptr->next != NULL)
	{
		i++;
		ptr = ptr->next;
	}
	str = malloc(i + sizeof(char) + 1);
	i = 0;
	while (entry->c == '\v' || entry->c == '\r' || entry->c == '\n' ||
			entry->c == '\t' || entry->c == '\f' || entry->c == ' ')
		entry = entry->next;
	while (entry->next != NULL)
	{
		str[i] = entry->c;
=======
	*entry_to_str(t_entry *entry)
{
	int i;
	t_entry *ptr;

	ptr = entry;
	i = 0;
	while (ptr->next != NULL)
	{
>>>>>>> e0e92544ea25f4909e5d5d23f8eabdd05b43a61b
		i++;
		ptr = ptr->next;
	}
	char *str = malloc(i * sizeof(char) + 1);
	int j = 0;
	while (j <= i)
	{
		str[j] = entry->c;
		j++;
		entry = entry->next;
	}
<<<<<<< HEAD
	str[i] = entry->c;
=======
	str[j] = '\0';
>>>>>>> e0e92544ea25f4909e5d5d23f8eabdd05b43a61b
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

void
	ft_get_pwd()
{
	char str[50];
	
	getcwd(str, 50);
	ft_putstr(str);
	ft_putstr("\n");
}

int
	ft_is_space(char *str)
{
	int i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\f' ||
		str[i] == '\n' || str[i] == '\r' || str[i] == '\v')
		i++;
	if (str[i] == '\0')
		return (1);
	else
		return (0);
}

void
	ft_wrong(char *str)
{
	int i = 0;
	if (!ft_is_space(str))
	{
		ft_putstr("minishell: ");
		while (str[i] == ' ' || str[i] == '\t' || str[i] == '\f' ||
			str[i] == '\n' || str[i] == '\r' || str[i] == '\v')
			i++;
		while (str[i] != ' ' && str[i] != '\t' && str[i] != '\f' &&
			str[i] != '\n' && str[i] != '\r' && str[i] != '\v' && str[i] != '\0')
		{
			write(1, &str[i], 1);
			i++;
		}

		ft_putstr(": command not found\n");
	}
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
<<<<<<< HEAD
			if (i > 0)
			{
				char *str = lst_to_str(entry);
				if (check_first_arg(str, "exit"))
					shell->is_active = 0;
				if (check_first_arg(str, "pwd"))
				{
					char pwd[50];
					getcwd(pwd, 50);
					ft_putstr(pwd);
					ft_putstr("\n");
				}
				if (check_first_arg(str, "leaks"))
					system("leaks minishell");
				if (check_first_arg(str, "recomp"))
				{
					system("sh test.sh");
					exit(0);
				}
=======
			// free the entry
			if (entry)
			{
				char *str = entry_to_str(entry);
				if (ft_strcmp(str, "exit") == 0)
					shell->is_active = 0;
				else if (ft_strcmp(str, "pwd") == 0)
					ft_get_pwd();
				else if (ft_strcmp(str, "leaks") == 0)
					system("leaks minishell");
				else
					ft_wrong(str);
>>>>>>> e0e92544ea25f4909e5d5d23f8eabdd05b43a61b
				free(str);
				ft_lstclear(&entry);
			}
			if (shell->is_active)
				ft_putstr(shell->prefix);
<<<<<<< HEAD
			i = 0;
=======
			else
				ft_putstr("exit\n");
>>>>>>> e0e92544ea25f4909e5d5d23f8eabdd05b43a61b
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
