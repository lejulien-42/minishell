/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frtalleu <frtalleu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 14:46:45 by frtalleu          #+#    #+#             */
/*   Updated: 2020/12/13 19:41:30 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _MINISHELL_H
# define _MINISHELL_H
# include <unistd.h>
# include <stdlib.h>
# include "../libft/libft.h"
# include <fcntl.h>
# include <signal.h>

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

typedef struct	s_exinfo
{
	char		**env;
	char		**av;
}				t_exinfo;

/*
** structure pour les variables globales du shell
*/

typedef struct	s_shell
{
	char		prefix[64];
	int			is_active;
	t_envars	**envp;
	int			sig_quit;
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
	char			*arg;
	struct s_arg	*next;
}				t_arg;

typedef struct	s_info_fork
{
	int			ret;
	int			is_pipe;
}				t_info_fork;

/*
** Liste chainee pour le parsing des entrees
*/

typedef struct	s_parse
{
	t_arg			*ar;
	char			*sep;
	int				pipes[2];
	int				is_next_pipe;
	int				fd;
	t_shell			*shell;
	struct s_parse	*next;
	struct s_parse	*prev;
}				t_parse;

void			ft_putstr(char *str);
int				ft_strcmp(const char *s1, const char *s2);
void			ft_strcpy(char *dest, char *src);
void			ft_putchar(char c, int fd);
void			ft_putnbr_fd(int nb, int fd);
void			get_pwd(t_shell *shell);
int				ft_is_space(char *str);
void			ft_wrong(char *str);
t_entry			*lst_skip_white_space(t_entry *entry);
char			*lst_to_str(t_entry *entry);
void			ft_lstclear(t_entry **lst);
t_entry			*add_entry(t_entry *prev_entry, char c);
t_shell			init_shell(void);
int				check_first_arg(char *entry, char *presumed_entry);
int				is_sep(char c);
int				cp_sep(char *str, char **to_fill);
t_parse			*init_struct_parse(void);
t_arg			*init_arg(void);
t_arg			*add_arg(t_arg *dest, t_arg *src);
char			*cut_arg(char *str);
int				backslash_dc(char c);
int				backslash_wc(char c);
int				fill_simple(char **dest, char *src);
int				fill_dollar(char **dest, char *src, t_shell *shell);
int				fill_backslash(char **dest, char *src, int(*f)(char));
char			*dw_cote_built(char *str, t_shell *shell, int(*f)(char));
int				manage_double_cote(char **dest, char *str, t_shell *shell,
				int(*f)(char));
int				manage_simple_cote(char **dest, char *str);
int				manage_without_cote(char **dest, char *str,
				t_shell *shell, int(*f)(char));
char			*manage_arg(char *str, t_shell *shell);
int				size_arg(char *str);
t_parse			*take_arg(char *str, t_parse *res, t_shell *shell);
t_parse			*parser(char *str, t_shell *shell);
char			*ft_strjoindf(char *s1, char *s2);
char			*ft_strndup(char *c, int i);
void			parse_entry(t_entry *entry, t_shell *shell);
void			entry_checker(char *str, t_shell *shell);
t_envars		*ft_get_envp(char ***envp, t_envars *env);
void			ft_print_env(t_envars *env);
void			set_env(char *name, char *value, int visib, t_envars **envp);
char			*get_env_val(char *name, t_envars **envp);
void			unset_env(char *name, t_envars **envp);
void			unset(t_shell *shell, t_parse *node);
void			export_env(t_shell *shell, t_parse *node, int out);
int				is_prog(char *cmd, t_shell *shell, t_parse *node);
char			**ft_env_back(t_envars **envp);
char			**ft_get_av(t_arg *arg);
void			free_tab(char **tab);
void			cd(t_shell *shell, t_parse *parse);
void			ft_echo(t_shell *shell, t_parse *parse);
int				is_built_in(t_parse *node, t_shell *shell);
void			ex_built_in(t_parse *node, t_shell *shell);
void			export_env2(char *name, t_arg *ptr, t_shell *shell, int i);
int				len_equal(char *str);
void			set_if_next_arg(char *name, t_arg *ptr, t_shell *shell);
int				do_built_in(t_parse *node, t_shell *shell);
void			get_inputs2(int *i, t_shell *shell);
void			parse_and_clear(t_entry **entry, t_shell *shell);
int				is_exist(char *path);
int				skip_if_red(t_parse *node);
void			close_redirect(t_parse *node);
void			execute_prog(char *path, t_shell *shell, t_parse *node);
int				nb_word(char *str, char c);
void			execute(char *path, t_exinfo *info, t_parse *node);
void			check_redirect2(t_parse *node);
int				is_prog3(t_shell *shell, char **path, t_parse *node,
				char *tested);
int				initialize_pipe(t_parse *node, int *is_pipe);
int				execute2(t_parse *node);
void			check_redirect(t_parse *node);
void			get_inputs3(int ret, int is_entry);
void			close_pipes(int is_pipe, t_parse *node);
int				open_pipes(t_parse *node, t_exinfo *info, char *path, int *ret);
int				init_fork(int *is_pipe, t_parse *node, int *pid);
void			red_file(t_parse *ptr);
int				is_num(char *str);
void			red_dup(t_parse *ptr);
int				is_seppa(char *str);
int				manage_wc2(char *str);
int				check_and_ex(char **path, char *cmd, t_shell *shell,
				t_parse *node);
int				is_prog2(t_parse *node, t_shell *shell, char *cmd);
int				checkfiles_ex(t_parse *node, struct stat sb);
int				check_pipe_ex(t_parse *node, t_shell *shell, char *cmd);
void			get_inputs_error(t_shell *shell, int *i);
void			get_inputs(t_shell *shell, int *i);
#endif
