/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <lejulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 16:46:22 by lejulien          #+#    #+#             */
/*   Updated: 2020/12/10 18:51:50 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <errno.h>
#include <dirent.h>

extern int	g_error;

void
	check_redirect(t_parse *node)
{
	t_parse *ptr;

	ptr = node;
	while (ptr->next && ptr->next->sep && (ft_strncmp(ptr->sep, ">",
		ft_strlen(ptr->sep)) == 0 || ft_strncmp(ptr->sep, "<",
		ft_strlen(ptr->sep)) == 0 || ft_strncmp(ptr->sep, ">>",
		ft_strlen(ptr->sep)) == 0))
	{
		red_file(ptr);
		ptr = ptr->next;
	}
	if (ptr->sep && ft_strncmp(ptr->sep, "|", ft_strlen(ptr->sep)) == 0)
		red_dup2(ptr);
	else
		red_dup(ptr);
}

void
	execute(char *path, t_exinfo *info, t_parse *node)
{
	pid_t	pid;
	int		status;
	int		ret;
	int		is_pipe;

	init_fork(&is_pipe, node, &pid);
	if (pid < 0)
		return ;
	else if (pid == 0)
	{
		if (!open_pipes(node, info, path, &ret))
			return ;
		exit(ret);
	}
	else
	{
		waitpid(pid, &status, 0);
		close_pipes(is_pipe, node);
		if (WIFEXITED(status))
			g_error = WEXITSTATUS(status);
		if (WIFEXITED(status))
			ret = WIFEXITED(status);
		if (WIFSIGNALED(status))
			g_error = WTERMSIG(status);
	}
}

static int
	is_prog2(t_parse *node, t_shell *shell, char *cmd)
{
	struct stat	sb;
	if (skip_if_red(node))
		return (1);
	if (is_built_in(node, shell))
	{
		execute_prog("built-in", shell, node);
		return (1);
	}
	if (is_exist(cmd))
	{
		if (stat(cmd, &sb) == 0 && (sb.st_mode & S_IXUSR))
			execute_prog(cmd, shell, node);
		else
			return (0);
		return (1);
	}
	return (0);
}

int
	is_seppa(char *str)
{
	if (ft_strncmp(str, ">", ft_strlen(str)) == 0)
		return (1);
	else if (ft_strncmp(str, ">>", ft_strlen(str)) == 0)
		return (1);
	else if (ft_strncmp(str, "<", ft_strlen(str)) == 0)
		return (1);
	return (0);
}

int
	is_prog(char *cmd, t_shell *shell, t_parse *node)
{
	char	**path;
	int		i;
	char	*tested;
	char	*prepath;
	struct stat	sb;
	DIR			*dir;

	i = 0;
	if ((open(node->ar->arg, O_RDONLY) < 0 || !opendir(node->ar->arg)) && is_prog2(node, shell, cmd))
		return (1);
	if (!get_env_val("PATH", shell->envp))
		return (0);
	path = ft_split(get_env_val("PATH", shell->envp), ":");
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
		else
		{
			if (open(node->ar->arg, O_RDONLY) < 0)
			{
				ft_putstr("\e[95mminichill\e[92m: \e[39m");
				ft_putstr(node->ar->arg);
				ft_putstr(": No such file or directory\n");
				set_env("?", "127", 0, shell->envp);
				return (1);
			}
		}
		i++;
	}
	if (node->prev && node->prev->sep && is_seppa(node->prev->sep) && node->sep
		&& ft_strncmp(node->sep, "|", ft_strlen(node->sep)) == 0)
	{
		
	}
	if (node->prev && node->prev->sep && is_seppa(node->prev->sep))
	{
		return (1);
	}
	dir = opendir(node->ar->arg);
	if (dir)
	{
		if (ft_strlen (node->ar->arg) > 1 && node->ar->arg[0] == '.' &&
						node->ar->arg[1] == '/')
		{
			ft_putstr("\e[95mminichill\e[92m: \e[39m");
			ft_putstr(node->ar->arg);
			ft_putstr(": Is a directory\n");
		}
		else
		{
			ft_putstr("\e[95mminichill\e[92m: \e[39m");
			ft_putstr(node->ar->arg);
			ft_putstr(": command not found\n");
		}
		return (1);
	}
	if (open(node->ar->arg, O_RDONLY) >= 0)
	{
		if (ft_strlen(node->ar->arg) > 1 && node->ar->arg[0] == '.' &&
			node->ar->arg[1] == '/')
		{
			if (stat(node->ar->arg, &sb) == 0 && (sb.st_mode & S_IXUSR))
			{
			}
			else
			{
				ft_putstr("\e[95mminichill\e[92m: \e[39m");
				ft_putstr(node->ar->arg);
				ft_putstr(": Permission denied\n");
				return (1);
			}
		}
		else
		{
			ft_putstr("\e[95mminichill\e[92m: \e[39m");
			ft_putstr(node->ar->arg);
			ft_putstr(": command not found\n");
			return (1);
		}
	}
	free_tab(path);
	return (0);
}
