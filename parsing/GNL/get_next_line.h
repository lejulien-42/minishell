/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frtalleu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 05:51:11 by frtalleu          #+#    #+#             */
/*   Updated: 2019/11/27 02:16:59 by frtalleu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stddef.h>
#include "../libft/libft.h"

typedef struct	s_char
{
	char	*lin;
	char	*stat;
}				t_char;

int				ft_checkline(char *str);
t_char			*ft_cut(char *str);
int				get_next_line(int fd, char **line);
char			*ft_read(int fd, char **rest);
#endif
