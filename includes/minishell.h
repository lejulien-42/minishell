/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/05 21:08:15 by lejulien          #+#    #+#             */
/*   Updated: 2020/07/13 16:21:28 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _MINISHELL_H
# define _MINISHELL_H
# include <unistd.h>
# include <stdlib.h>
/*
** structure pour les variables globales du shell
*/

typedef struct	s_shell
{
	char	prefix[64];
	int		is_active;
}				t_shell;

/*
** Liste chainée pour le parsing des entrées
*/

typedef struct	s_entry
{
	char	c;
	void	*next;
}				t_entry;

/*
** Liste des variables d'environement
**
** contient le nom et la valeur d'une variable
** et l'adresse de la suivante
** visibility = 1 si var exported
*/

typedef struct	s_envars
{
	char	*var_name;
	char	*var_value;
	int		visibility;
	void	*next;
}				t_envars;


void			ft_putstr(char *str);
int				ft_strcmp(const char *s1, const char *s2);
void			ft_strcpy(char *dest, char *src);
void			ft_putchar(char c, int fd);
void			ft_putnbr_fd(int nb, int fd);
void			get_pwd(void);
int				ft_is_space(char *str);
void			ft_wrong(char *str);
t_entry			*lst_skip_white_space(t_entry *entry);
char			*lst_to_str(t_entry *entry);
#endif
