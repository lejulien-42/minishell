/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 03:32:58 by lejulien          #+#    #+#             */
/*   Updated: 2020/11/17 16:14:21 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char
	*ft_strldup(char *str, int len)
{
	char	*res;
	int		i;

	i = 0;
	res = malloc((len + 1) * sizeof(char));
	while (str[i] != '\0' && i < len)
	{
		res[i] = str[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

static int
	len_equal(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i] != '\0')
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (-1);
}

static void
	set_if_next_arg(char *name, t_arg *ptr, t_shell *shell)
{
	ptr = ptr->next;
	set_env(name, ptr->arg, 1, shell->envp);
}

void
	ft_print_env_ex(t_envars *env)
{
	t_envars	*ptr;
	
	ptr = env;
	while (ptr != NULL)
	{
		ft_putstr("export ");
		ft_putstr(ptr->name);
		ft_putstr("=");
		ft_putstr(ptr->value);
		ft_putstr("\n");
		ptr = ptr->next;
	}
}

void
	export_env(t_shell *shell, t_parse *node, int out)
{
	t_arg	*ptr;
	char	*name;
	int		i;

	ptr = node->ar->next;
	if (!node->ar->next && out)
		ft_print_env_ex(*shell->envp);
	while (ptr)
	{
		if (len_equal(ptr->arg) > 0)
		{
			i = 0;
			name = ft_strldup(ptr->arg, len_equal(ptr->arg));
			while (ptr->arg[i] != '=')
				i++;
			i++;
			if (ft_strlen(ptr->arg) > len_equal(ptr->arg))
				set_env(name, &ptr->arg[i], 1, shell->envp);
			else if (ptr->next != NULL)
				set_if_next_arg(name, ptr, shell);
			else
				set_env(name, "\0", 1, shell->envp);
			free(name);
		}
		ptr = ptr->next;
	}
}
