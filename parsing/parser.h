/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frtalleu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 11:35:19 by frtalleu          #+#    #+#             */
/*   Updated: 2020/07/19 11:35:20 by frtalleu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _PARSER_H
# define _PARSER_H

# include <unistd.h>
# include <stdlib.h>

typedef struct	s_arg
{
	char *argu;
	void *next;
}				t_arg;

typedef struct	s_parse
{
	char		*cmd;
	char		*flag;
	t_arg		*arg;
	char		*sep;
	void		*next;
}				t_parse;

int				cp_until_space(char *str, char **st);
int				is_sep(char *str);
int				cp_sep(char *str, char **to_fill);
int				cp_until_cote(char *str, char **to_fill);
t_parse			*init_struct_parse(void);
t_parse			*parser(char *str);
#endif
