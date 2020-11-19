/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <lejulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 16:46:22 by lejulien          #+#    #+#             */
/*   Updated: 2020/11/19 17:35:37 by lejulien         ###   ########.fr       */
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
	execute(char *path, char **av, char **envp, t_parse *node)
{
	pid_t	pid;
	int		status;
	int		ret;
	int		is_pipe;

	ret = EXIT_FAILURE;
	is_pipe = 0;
	if (!initialize_pipe(node, &is_pipe))
		return (0);
	pid = fork();
	if (pid < 0)
		return (0);
	else if (pid == 0)
	{	
		if (!execute2(node))
			return (0);
		if (is_built_in(node, node->shell))
			ex_built_in(node, node->shell);
		else if (node->fd != -1 && (ret = execve(path, av, envp)) < 0)
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

char
	**ft_split2(char *st, char *c)
{
	int		i;
	int		j;
	int		word;
	char	**tab;
	char	*str;

	str = ft_strdup(st);
	j = 0;
	word = nb_word(str, c[0]);
	if ((i = 0) || !(tab = malloc(sizeof(char *) * (word + 1))))
		return (NULL);
	while (!(word = 0) && str[i] == c[0])
		i++;
	while (str[i] != '\0')
	{
		while (str[i + j] != c[0] && str[i + j] != '\0')
			j++;
		while (str[i + j] == c[0])
			j++;
		if (str[i + j - 1] == c[0])
			str[i + j - 1] = '\0';
		tab[word++] = ft_strtrim(&str[i], c);
		i = i + j;
		j = 0;
	}
	tab[word] = 0;
	free(str);
	return (tab);
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
	path = ft_split2(get_env_val("PATH", shell->envp), ":");
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
