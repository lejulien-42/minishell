/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/05 21:08:15 by lejulien          #+#    #+#             */
/*   Updated: 2020/07/05 22:22:28 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _MINISHELL_H
# define _MINISHELL_H

// structure pour les variables globales du shell
typedef struct	s_shell
{
	char	prefix[64];
	int		is_active;
}				t_shell;

// Liste chainée pour le parsing des entrées
typedef struct	s_entry
{
	char	c;
	void	*next;
}				t_entry;
#endif
