/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/05 21:08:15 by lejulien          #+#    #+#             */
/*   Updated: 2020/07/26 03:12:57 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _MINISHELL_H
# define _MINISHELL_H
# include <unistd.h>
# include <stdlib.h>
# include "../libft/libft.h"

/*
** Liste des variables d'environement
**
** contient le nom et la valeur d'une variable
** et l'adresse de la suivante
** visibility = 1 si var exported
*/

typedef struct	s_envars
{
	char		*name;
	char		*value;
	int			visibility;
	void		*next;
}				t_envars;

/*
** structure pour les variables globales du shell
*/

typedef struct	s_shell
{
	char		prefix[64];
	int			is_active;
	t_envars	**envp;
}				t_shell;

/*
** Liste chainée pour le parsing des entrées
*/

typedef struct	s_entry
{
	char		c;
	void		*next;
}				t_entry;

/*
** Liste chainee pour les arguments
*/

typedef struct	s_arg
{
	char		*argu;
	void		*next;
}				t_arg;

/*
** Liste chainee pour le parsing des entrees
*/

typedef struct	s_parse
{
	char	*cmd;
	char	*flag;
	t_arg	*arg;
	char	*sep;
	void	*next;
}				t_parse;

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
void			ft_lstclear(t_entry **lst);
t_entry			*add_entry(t_entry *prev_entry, char c);
t_shell			init_shell(void);
int				check_first_arg(char *entry, char *presumed_entry);
void			parse_entry(t_entry *entry, t_shell *shell);
void			entry_checker(char *str, t_shell *shell);
int				cp_until_space(char *str, char **st);
int				is_sep(char *str);
int				cp_sep(char *str, char **to_fill);
int				cp_until_cote(char *str, char **to_fill);
t_parse			*init_struct_parse(void);
t_parse			*parser(char *str);
t_arg			*init_arg(void);
t_parse			*init_struct_parse(void);
int				add_arg(t_parse *res, char *str);
void			ft_free_parse(t_parse *res);
void			ft_free_arg(t_arg *arg);
t_envars		*ft_get_envp(char ***envp, t_envars *env);
void			ft_print_env(t_envars *env);
void			set_env(char *name, char *value, int visib, t_envars **envp);
char			*get_env_val(char *name, t_envars **envp);
void			unset_env(char *name, t_envars **envp);
void			unset(t_shell *shell, t_parse *node);
#endif
