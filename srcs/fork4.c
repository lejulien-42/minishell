/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 18:02:40 by lejulien          #+#    #+#             */
/*   Updated: 2020/12/13 19:15:54 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <dirent.h>
#include <sys/stat.h>

void
	ft_printf_shell_error(char *arg, char *str)
{
	ft_putstr("\e[95mminichill\e[92m: \e[39m");
	ft_putstr(arg);
	ft_putstr(str);
}

int
	checkfiles_ex(t_parse *node, struct stat sb)
{
	DIR	*dir;

	dir = opendir(node->ar->arg);
	if (dir)
	{
		if (ft_strlen(node->ar->arg) > 1 && node->ar->arg[0] == '.' &&
						node->ar->arg[1] == '/')
			ft_printf_shell_error(node->ar->arg, ": Is a directory\n");
		else
			ft_printf_shell_error(node->ar->arg, ": command not found\n");
		return (1);
	}
	if (open(node->ar->arg, O_RDONLY) >= 0 && ft_strlen(node->ar->arg) > 1 &&
		node->ar->arg[0] == '.' && node->ar->arg[1] == '/' &&
		!(stat(node->ar->arg, &sb) == 0 && (sb.st_mode & S_IXUSR)))
	{
		ft_printf_shell_error(node->ar->arg, ": Permission denied\n");
		return (1);
	}
	else
	{
		ft_printf_shell_error(node->ar->arg, ": command not found\n");
		return (1);
	}
	return (0);
}

int
	check_pipe_ex(t_parse *node, t_shell *shell, char *cmd)
{
	if (node->prev && node->prev->sep && is_seppa(node->prev->sep) && node->sep
		&& ft_strncmp(node->sep, "|", ft_strlen(node->sep)) == 0)
		is_prog3(shell, NULL, node, node->ar->arg);
	if (((open(node->ar->arg, O_RDONLY) < 0 || !opendir(node->ar->arg))) &&
		is_prog2(node, shell, cmd))
		return (1);
	return (0);
}

int
	check_and_ex(char **path, char *cmd, t_shell *shell, t_parse *node)
{
	int		i;
	char	*prepath;
	char	*tested;

	i = 0;
	while (path[i])
	{
		if (ft_strlen(cmd) < 2 || (cmd[0] != '.' && cmd[1] != '/'))
		{
			prepath = ft_strjoin("/", cmd);
			tested = ft_strjoin(path[i], prepath);
			free(prepath);
			if (is_prog3(shell, path, node, tested))
				return (1);
		}
		else if (open(node->ar->arg, O_RDONLY) < 0)
		{
			ft_printf_shell_error(node->ar->arg,
				": No such file or directory\n");
			set_env("?", "127", 0, shell->envp);
			return (1);
		}
		i++;
	}
	return (0);
}

void
	get_inputs_error(t_shell *shell, int *i)
{
	while (shell->is_active)
		get_inputs(shell, i);
	if (!is_num(get_env_val("?", shell->envp)))
	{
		ft_putstr(get_env_val("?", shell->envp));
		set_env("?", "2", 0, shell->envp);
	}
}
