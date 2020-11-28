/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 16:46:13 by lejulien          #+#    #+#             */
/*   Updated: 2020/11/28 19:40:20 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_error;

int
	nb_word(char *str, char c)
{
	int i;
	int nb;

	i = 0;
	nb = 0;
	while (str[i] != '\0')
	{
		if (str[i] != c)
			nb++;
		while (str[i] != c && str[i] != '\0')
			i++;
		while (str[i] == c)
			i++;
	}
	return (nb);
}

void
	execute_prog(char *path, t_shell *shell, t_parse *node)
{
	t_exinfo	*info;
	char		*tmp;

	if (!(info = malloc(sizeof(t_exinfo))))
		return ;
	info->env = ft_env_back(shell->envp);
	info->av = ft_get_av(node->ar);
	node->shell = shell;
	execute(path, info, node);
	if (g_error == 11)
	{
		ft_putstr("Segmentation fault (core dumped)\n");
		g_error = 139;
	}
	if (is_built_in(node, node->shell))
		g_error = 0;
	tmp = ft_itoa(g_error);
	set_env("?", tmp, 0, shell->envp);
	free(tmp);
	free_tab(info->av);
	free_tab(info->env);
	free(info);
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
	t_parse	*ptr;

	ptr = node;
	while (ptr->prev && ptr->prev->sep && (ft_strncmp(ptr->prev->sep, ">",
		ft_strlen(node->prev->sep)) == 0 || ft_strncmp(ptr->prev->sep, "<",
		ft_strlen(node->prev->sep)) == 0 || ft_strncmp(ptr->prev->sep, "<",
		ft_strlen(node->prev->sep)) == 0))
	{
		if (ptr->prev && ptr->prev->sep && ft_strncmp(ptr->prev->sep,
			">", ft_strlen(ptr->prev->sep)) == 0)
			return (1);
		if (ptr->prev && ptr->prev->sep && ft_strncmp(ptr->prev->sep,
			"<", ft_strlen(ptr->prev->sep)) == 0)
			return (1);
		if (ptr->prev && ptr->prev->sep && ft_strncmp(ptr->prev->sep,
			">>", ft_strlen(ptr->prev->sep)) == 0)
			return (1);
		ptr = ptr->next;
	}
	node = ptr->prev;
	return (0);
}

int
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
