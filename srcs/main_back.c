/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_back.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/05 18:50:15 by lejulien          #+#    #+#             */
/*   Updated: 2020/07/13 20:31:05 by lejulien         ###   ########.fr       */
/*   Updated: 2020/07/06 23:06:03 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "../includes/minishell.h"
#include "../libft/libft.h"

int
	main(void)
{
	char buffer[2];
	int i = 0;
	t_entry	entry;
	buffer[1] = '\0';
	t_shell	shell = init_shell();
	ft_putstr(shell.prefix);
	while (shell.is_active)
	{
		read(0, buffer, 1);
		buffer[1] = '\0';
		if (buffer[0] == '\n')
		{
			/*
			if (i > 0)
			{
				char *str;
			   	str = lst_to_str(entry);
				if (!ft_is_space(str))
				{
						
					if (check_first_arg(str, "exit"))
						shell->is_active = 0;
					else if (check_first_arg(str, "leaks"))
						system("leaks minishell");
					else if (check_first_arg(str, "pwd"))
						get_pwd();
					else if (check_first_arg(str, "make coffee"))
						ft_putstr("☕️\n");
					else
						ft_wrong(str);
					
				}
				free(str);
				ft_lstclear(&entry);
			}
			*/
			parse_entry(&i, &entry, &shell);
			if (shell.is_active)
				ft_putstr(shell.prefix);
			else
				ft_putstr("exit\n");
			i = 0;
		}
		else
		{
			if (i >= 0)
			{
				entry = add_entry(&entry, buffer[0]);
				i++;
			}
		}
	}
	return (0);
}
