/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 16:58:04 by lejulien          #+#    #+#             */
/*   Updated: 2020/07/21 17:12:33 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void
	parse_and_clear(t_entry **entry, t_shell *shell)
{
	char	*str;

	str = lst_to_str(*entry);
	if (!ft_is_space(str))
		entry_checker(str, shell);
	free(str);
	ft_lstclear(entry);
}

static void
	get_inputs(t_shell *shell, int *i)
{
	static t_entry	*entry = NULL;
	char			buffer[2];

	read(0, buffer, 1);
	buffer[1] = '\0';
	if (buffer[0] == '\n')
	{
		if (*i > 0)
			parse_and_clear(&entry, shell);
		if (shell->is_active)
			ft_putstr(shell->prefix);
		else
			ft_putstr("exit\n");
		*i = 0;
	}
	else
	{
		entry = add_entry(entry, buffer[0]);
		*i = *i + 1;
	}
}

int
	main(int ac, char **av, char **envp)
{
	t_shell	shell;
	int		i;

	(void)ac;
	(void)av;
	i = 0;
	shell = init_shell();
	shell.envp = &envp;
	ft_putstr(shell.prefix);
	while (shell.is_active)
		get_inputs(&shell, &i);
	return (0);
}
