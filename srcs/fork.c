/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <lejulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 16:46:22 by lejulien          #+#    #+#             */
/*   Updated: 2020/07/30 16:15:02 by lejulien         ###   ########.fr       */
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
	if (pid == -1)
	{}//	return (-1);
	else if (pid == 0)
	{
		if ((ret = execve(path, av, envp)) < 0)
			return (-1);
		exit(ret);
	}
	else
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
	av = ft_get_av(node->arg);
	execute(path, av, env);
	// Free env & av
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
			return (1);
		}
		free(tested);
		i++;
	}
	// Free path please
	return (0);
}
