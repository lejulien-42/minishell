/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frtalleu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 11:34:45 by frtalleu          #+#    #+#             */
/*   Updated: 2020/07/19 11:34:46 by frtalleu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "./parser.h"
#include "stdio.h"
#include "GNL/get_next_line.h"

/*int	is_sep(char *str)
  {
  if (str[0] != '<' && str[0] != '>' && str[0] != '|' && str[0] != ';')
  return (1);
  return (0);
  }

  int	cp_until_space(char *str, char **to_fill)
  {
  int		i;
  char	*st;

  i = 0;
  while (str[i] != ' ' && str[i] != '\0' && is_sep(&str[i]) == 1)
  i++;
  if (!(st = malloc(sizeof(char) * (i + 1))))
  return (0);
  i = 0;
  while (str[i] != ' ' && str[i] != '\0' && is_sep(&str[i]) == 1)
  {
  st[i] = str[i];
  i++;
  }
  st[i] = '\0';
 *to_fill = st;
 return (i);
 }

 int	cp_sep(char *str, char **to_fill)
 {
 int		i;
 char	*st;

 i = 0;
 while (is_sep(&str[i]) == 0)
 i++;
 if (!(st = malloc(sizeof(char) * (i + 1))))
 return (0);
 i = 0;
 while (is_sep(&str[i]) == 0)
 {
 st[i] = str[i];
 i++;
 }
 st[i] = '\0';
 *to_fill = st;
 return (i);
 }

 int	cp_until_cote(char *str, char **to_fill)
 {
 int		i;
 char	*st;

 i = 1;
 while (str[i] != str[0] && str[i] != '\0')
 i++;
 if (str[i] != str[0])
 return (-1);
 if (!(st = malloc(sizeof(char) * i)))
 return (0);
 i = 1;
 while (str[i] != str[0])
 {
 st[i - 1] = str[i];
 i++;
 }
 st[i - 1] = '\0';
 *to_fill = st;
 return (i);
 }

t_parse	*init_struct_parse(void)
{
	t_parse *res;

	if (!(res = malloc(sizeof(*res))))
		return (NULL);
	res->cmd = NULL;
	res->flag = NULL;
	res->arg = NULL;
	res->sep = NULL;
	res->next = NULL;
	return (res);
}

t_parse	*parser(char *str)
{
	t_parse	*res;
	int		i;

	i = 0;
	res = init_struct_parse();
	while (str[i] == ' ')
		i++;
	i = i + cp_until_space(&str[i], &res->cmd);
	while (str[i] == ' ')
		i++;
	if (str[i] == '-')
		i = i + 1 + cp_until_space(&str[i + 1], &res->flag);
	while (str[i] == ' ')
		i++;
	if (str[i] == '"' || str[i] == '\'')
		i = i + cp_until_cote(&str[i], &res->arg);
	else if (is_sep(&str[i]) == 1)
		i = i + cp_until_space(&str[i], &res->arg);
	while (str[i] == ' ')
		i++;
	if (is_sep(&str[i]) == 0)
		res->next = parser(&str[i + cp_sep(&str[i], &res->sep)]);
	return (res);
}
*/

int main(void)
{
	char *line;
	t_parse *res;
	t_arg *argus;
	write(1, "zsh$>", 5);
	while ((get_next_line(0, &line)) == 1)
	{
		printf("line = |%s|\n", line);
		res = parser(line);
		printf("cmd = |%s|\n", res->cmd);
		printf("flag = |%s|\n", res->flag);
		if (res->arg != NULL)
		{
			argus = res->arg;
			printf("arg = |%s|\n", argus->argu);
			while (argus->next != NULL && (argus = argus->next))
			{
				printf("arg = |%s|\n", argus->argu);
			}
		}
		printf("sep = |%s|\n", res->sep);
		while (res->next != NULL)
		{
			res = res->next;
			printf("cmd = |%s|\n", res->cmd);
			printf("flag = |%s|\n", res->flag);
			if (res->arg != NULL)
			{
				argus = res->arg;
				printf("arg = |%s|\n", argus->argu);
				while (argus->next != NULL && (argus = argus->next))
				{
					printf("arg = |%s|\n", argus->argu);
				}
			}
			printf("sep = |%s|\n", res->sep);
		}
		write(1, "zsh$>", 5);
	}
}
