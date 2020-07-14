/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 16:58:04 by lejulien          #+#    #+#             */
/*   Updated: 2020/07/14 18:46:49 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void
	get_inputs(t_shell *shell, int *i)
{
	t_entry	entry;
	char	buffer[2];

	read(0, buffer, 1);
	buffer[1] = '\0';
	if (buffer[0] == '\n')
	{
		/*
		if (i > 0)
			parse_entry(&entry, shell);
		*/
		if (shell->is_active)
			ft_putstr(shell->prefix);
		else
			ft_putstr("exit\n");
		*i = 0;
	}
	else
		add_entry(&entry, buffer[0]);
	*i = *i + 1;
}

int
	main(void)
{
	t_shell	shell;
	int i;

	i = 0;
	shell = init_shell();
	ft_putstr(shell.prefix);
	while (shell.is_active)
		get_inputs(&shell, &i);
	return(0);
}
