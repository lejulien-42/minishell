/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <lejulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 16:46:22 by lejulien          #+#    #+#             */
/*   Updated: 2020/08/02 16:10:41 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int
	execute(char *path, char **av, char **envp)
{
	pid_t	pid;
	int		status;
	int		ret;

	int	i = 0;
	while (av[i])
	{
		ft_putstr(av[i]);
		ft_putstr("\n");
		i++;
	}
	pid = fork();
	if (pid == 0)
	{
		if ((ret = execve(path, av, envp)) < 0)
			return (-1);
		exit(ret);
	}
	else if (pid != -1)
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			ret = WIFEXITED(status);
	}
	return (1);
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
	execute(path, av, env);
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
