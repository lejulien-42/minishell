/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <lejulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 16:46:22 by lejulien          #+#    #+#             */
/*   Updated: 2020/11/24 15:40:41 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

extern int	g_error;

void
	check_redirect(t_parse *node)
{
	if (ft_strncmp(node->sep, ">", ft_strlen(node->sep)) == 0)
	{
		if (node->next && node->next->ar->arg)
		{
			node->fd = open(node->next->ar->arg, O_CREAT | O_RDWR |
							O_TRUNC, 0664);
			dup2(node->fd, 1);
		}
	}
	if (ft_strncmp(node->sep, "<", ft_strlen(node->sep)) == 0)
		check_redirect2(node);
	if (ft_strncmp(node->sep, ">>", ft_strlen(node->sep)) == 0)
	{
		if (node->next && node->next->ar->arg)
		{
			node->fd = open(node->next->ar->arg, O_CREAT | O_APPEND |
							O_WRONLY, 0664);
			dup2(node->fd, 1);
		}
	}
}

int
	execute(char *path, t_exinfo *info, t_parse *node)
{
	pid_t	pid;
	int		status;
	int		ret;
	int		is_pipe;

	init_fork(&is_pipe, node, &pid);
	if (pid < 0)
		return (0);
	else if (pid == 0)
	{
		if (!open_pipes(node, info, path, &ret))
			return (0);
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
	return (ret);
}

static int
	is_prog2(t_parse *node, t_shell *shell, char *cmd)
{
	if (skip_if_red(node))
		return (1);
	if (is_built_in(node, shell))
	{
		execute_prog("built-in", shell, node);
		return (1);
	}
	if (is_exist(cmd))
	{
		execute_prog(cmd, shell, node);
		return (1);
	}
	return (0);
}

int
	is_prog(char *cmd, t_shell *shell, t_parse *node)
{
	char	**path;
	int		i;
	char	*tested;
	char	*prepath;

	i = 0;
	if (is_prog2(node, shell, cmd))
		return (1);
	if (!get_env_val("PATH", shell->envp))
		return (0);
	path = ft_split(get_env_val("PATH", shell->envp), ":");
	while (path[i])
	{
		prepath = ft_strjoin("/", cmd);
		tested = ft_strjoin(path[i], prepath);
		free(prepath);
		if (is_prog3(shell, path, node, tested))
			return (1);
		i++;
	}
	free_tab(path);
	return (0);
}
