/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <lejulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 16:46:22 by lejulien          #+#    #+#             */
/*   Updated: 2020/11/06 12:02:42 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <sys/types.h>
#include <sys/wait.h>

void
	check_redirect(t_parse *node)
{
	if (ft_strncmp(node->sep, ">", ft_strlen(node->sep)) == 0)
	{
		if (node->next && node->next->ar->arg)
		{
			node->fd = open(node->next->ar->arg, O_CREAT | O_RDWR | O_TRUNC, 0664);
			dup2(node->fd, 1);
		}
	}
	if (ft_strncmp(node->sep, "<", ft_strlen(node->sep)) == 0)
	{
		if (node->next && node->next->ar->arg)
		{
			node->fd = open(node->next->ar->arg, O_RDONLY);
			dup2(node->fd, 0);
		}
	}
	if (ft_strncmp(node->sep, ">>", ft_strlen(node->sep)) == 0)
	{
		if (node->next && node->next->ar->arg)
		{
			node->fd = open(node->next->ar->arg, O_CREAT | O_APPEND | O_WRONLY, 0664);
			dup2(node->fd, 1);
		}
	}
}

void
	close_redirect(t_parse *node)
{
	if (ft_strncmp(node->sep, ">", ft_strlen(node->sep)) == 0)
		close(node->fd);
	if (ft_strncmp(node->sep, "<", ft_strlen(node->sep)) == 0)
		close(node->fd);
	if (ft_strncmp(node->sep, ">>", ft_strlen(node->sep)) == 0)
		close(node->fd);
}

int
	skip_if_red(t_parse *node)
{
	if (node->prev && node->prev->sep && ft_strncmp(node->prev->sep,
		">", ft_strlen(node->prev->sep)) == 0)
		return (1);
	if (node->prev && node->prev->sep && ft_strncmp(node->prev->sep,
		"<", ft_strlen(node->prev->sep)) == 0)
		return (1);
	if (node->prev && node->prev->sep && ft_strncmp(node->prev->sep,
		">>", ft_strlen(node->prev->sep)) == 0)
		return (1);
	return (0);
}

static int
	execute(char *path, char **av, char **envp, t_parse *node)
{
	pid_t	pid;
	int		status;
	int		ret;
	int		is_pipe;

	// Savoir si il y as eu un pipe
	ret = EXIT_FAILURE;
	is_pipe = 0;
	if ((node->sep  && ft_strncmp(node->sep, "|", ft_strlen(node->sep)) == 0) ||
		(node->prev && node->prev->is_next_pipe))
	{
		is_pipe = 1;
		if (node->sep && ft_strncmp(node->sep, "|", ft_strlen(node->sep)) == 0)
			node->is_next_pipe = 1;
		if (pipe(node->pipes))
			return (0);
	}
	pid = fork();
	if (pid < 0)
		return (0);
	else if (pid == 0)
	{
		if (node->is_next_pipe && dup2(node->pipes[1], 1) < 0)
			return (0);
		if (node->prev && node->prev->is_next_pipe == 1 &&
			dup2(node->prev->pipes[0], 0) < 0)
			return (0);
		if (node->sep)
			check_redirect(node);
		if (is_built_in(node, node->shell))
			ex_built_in(node, node->shell);
		else if ((ret = execve(path, av, envp)) < 0)
			return (0);
		if (node->sep)
			close_redirect(node);
		exit(ret);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (is_pipe)
		{
			close(node->pipes[1]);
			if (!node->next || (node->sep &&
				ft_strncmp(node->sep, ";", ft_strlen(node->sep)) == 0))
				close(node->pipes[0]);
		}
		if (node->prev && node->prev->is_next_pipe)
			close(node->prev->pipes[0]);
		if (WIFEXITED(status))
			ret = WIFEXITED(status);
	}
	return (ret);
}

static int
	is_exist(char *path)
{
	int	fd;

	if ((fd = open((const char *)path, O_RDONLY)) > 0)
	{
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

static void
	execute_prog(char *path, t_shell *shell, t_parse *node)
{
	char	**env;
	char	**av;

	env = ft_env_back(shell->envp);
	av = ft_get_av(node->ar);
	node->shell = shell;
	execute(path, av, env, node);
	free_tab(av);
	free_tab(env);
}

int
	is_prog(char *cmd, t_shell *shell, t_parse *node)
{
	char	**path;
	int		i;
	char	*tested;
	char	*prepath;

	i = 0;
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
	path	= ft_split(get_env_val("PATH", shell->envp), ':');
	while (path[i])
	{
		prepath = ft_strjoin("/", cmd);
		tested = ft_strjoin(path[i], prepath);
		free(prepath);
		if (is_exist(tested))
		{
			execute_prog(tested, shell, node);
			free(tested);
			free_tab(path);
			return (1);
		}
		free(tested);
		i++;
	}
	free_tab(path);
	return (0);
}
