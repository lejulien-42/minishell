/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 16:58:04 by lejulien          #+#    #+#             */
/*   Updated: 2020/10/20 15:47:22 by lejulien         ###   ########.fr       */
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
	int				ret;
	static int		is_entry = 0;

	ret = read(0, buffer, 1);
	if (ret == 0 && is_entry == 0)
	{
		//exit properly
		ft_putstr("exit\n");
		exit(0);
	}
	buffer[1] = '\0';
	if (buffer[0] == '\n')
	{
		is_entry = 0;
		if (*i > 0)
			parse_and_clear(&entry, shell);
		if (shell->is_active)
		{
			if (get_env_val("PS1", shell->envp) != NULL)
				ft_putstr(get_env_val("PS1", shell->envp));
		}
		else
			ft_putstr("exit\n");
		*i = 0;
	}
	else
	{
		if (ret != 0)
		{
			is_entry = 1;
			entry = add_entry(entry, buffer[0]);
			*i = *i + 1;
		}
	}
}

void
	get_ctrl_c(int nan)
{
	(void)nan;
}

int
	main(int ac, char **av, char **envp)
{
	t_shell		shell;
	int			i;
	t_envars	envars;
	t_envars	*lsenv;

	(void)ac;
	(void)av;
	i = 0;
	signal(SIGINT, get_ctrl_c);
	lsenv = ft_get_envp(&envp, &envars);
	shell = init_shell();
	shell.envp = &lsenv;
	set_env("PS1", "\e[95mminichill\e[92m$ \e[39m", 0, &lsenv);
	if (get_env_val("PS1", &lsenv) != NULL)
		ft_putstr(get_env_val("PS1", &lsenv));
	while (shell.is_active)
		get_inputs(&shell, &i);
	return (0);
}
