/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 16:58:04 by lejulien          #+#    #+#             */
/*   Updated: 2020/12/14 15:48:39 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_isex;
int	g_error;
int	g_isbs;

void
	parse_and_clear(t_entry **entry, t_shell *shell)
{
	char	*str;

	str = lst_to_str(*entry);
	if (!ft_is_space(str))
		entry_checker(str, shell);
	free(str);
	ft_lstclear(entry);
}

void
	get_inputs(t_shell *shell, int *i)
{
	char			buffer[2];
	int				ret;
	static int		is_entry = 0;

	ret = read(0, buffer, 1);
	get_inputs3(ret, is_entry, shell);
	buffer[1] = '\0';
	if (buffer[0] == '\n')
	{
		is_entry = 0;
		if (*i > 0)
			parse_and_clear(&shell->entry, shell);
		get_inputs2(i, shell);
	}
	else
	{
		if (ret != 0)
		{
			is_entry = 1;
			shell->entry = add_entry(shell->entry, buffer[0]);
			*i = *i + 1;
		}
	}
}

void
	signal_handler(int nan)
{
	if (nan == 2)
	{
		if (!g_isex)
			ft_putstr("\n\e[95mminichill\e[92m$ \e[39m");
	}
	if (nan == 3)
		g_isbs = 1;
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
	g_isbs = 0;
	signal(SIGQUIT, signal_handler);
	signal(SIGINT, signal_handler);
	if (*envp)
		lsenv = ft_get_envp(&envp, &envars);
	else
		lsenv = NULL;
	shell = init_shell();
	shell.envp = &lsenv;
	if (!lsenv)
		set_env("HOME", "/", 1, &lsenv);
	set_env("?", "0", 0, &lsenv);
	set_env("PS1", "\e[95mminichill\e[92m$ \e[39m", 0, &lsenv);
	if (get_env_val("PS1", &lsenv) != NULL)
		ft_putstr(get_env_val("PS1", &lsenv));
	get_inputs_error(&shell, &i);
	return (ft_atoi(get_env_val("?", shell.envp)));
}
