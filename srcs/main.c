/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 16:58:04 by lejulien          #+#    #+#             */
/*   Updated: 2020/08/18 18:14:37 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <signal.h>

int	g_ctrl_c = 0;

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
	process_entry(t_shell *shell, int *i, t_entry *entry)
{
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

static void
	get_inputs(t_shell *shell, int *i)
{
	static t_entry	*entry = NULL;
	char			buffer[2];
	int				ret;

	if (g_ctrl_c == 0)
		ret = read(0, buffer, 1);
	buffer[1] = '\0';
	if (g_ctrl_c == 2)
	{
		ft_putstr(get_env_val("PS1", shell->envp));
		ft_putstr("\n");
	}
	if (buffer[0] == '\n' || g_ctrl_c == 2)
		process_entry(shell, i, entry);
	else
	{
		entry = add_entry(entry, buffer[0]);
		*i = *i + 1;
	}
	g_ctrl_c = 0;
}

void
	get_gtrl_c(int nan)
{
	g_ctrl_c = nan;
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
	g_ctrl_c = 0;
	signal(SIGINT, get_gtrl_c);
	lsenv = ft_get_envp(&envp, &envars);
	shell = init_shell();
	shell.envp = &lsenv;
	shell.sig_quit = 0;
	set_env("PS1", "\e[95mminichill\e[92m$ \e[39m", 0, &lsenv);
	if (get_env_val("PS1", &lsenv) != NULL)
		ft_putstr(get_env_val("PS1", &lsenv));
	signal(SIGINT, get_gtrl_c);
	while (shell.is_active)
	{
		get_inputs(&shell, &i);
	}
	return (0);
}
