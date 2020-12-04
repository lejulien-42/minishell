# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lejulien <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/07/05 18:43:38 by lejulien          #+#    #+#              #
#    Updated: 2020/11/20 14:47:22 by lejulien         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = 	./srcs/main.c ./srcs/utils_0.c ./srcs/utils_1.c ./srcs/lst_to_str.c    \
		./srcs/utils_2.c ./srcs/shell_setup.c ./srcs/parse_helper.c            \
		./srcs/parser.c ./srcs/env.c ./srcs/set_env.c ./srcs/get_env.c 		   \
		./srcs/unset_env.c ./srcs/unset.c ./srcs/export.c ./srcs/fork.c 	   \
		./srcs/env_bask.c ./srcs/ft_strndup.c ./srcs/parser1.c ./srcs/parser2.c\
		./srcs/parser3.c ./srcs/cd.c ./srcs/echo.c ./srcs/built_in.c 		   \
		./srcs/export2.c ./srcs/parse_helper2.c ./srcs/fork2.c				   \
		./srcs/redirect.c ./srcs/is_prog.c ./srcs/get_inputs.c ./srcs/fork3.c

OBJS = ${SRCS:.c=.o}

FLAGS = -Wall -Wextra -Werror

.c.o:
	@gcc -c $< -o $(<:.c=.o)

NAME = minishell

$(NAME): $(OBJS)
	@$(MAKE) -C ./libft
	@gcc $(FLAGS) -o $(NAME) $(OBJS) ./libft/libft.a

clean:
	@$(MAKE) -C ./libft/. clean
	@rm -f $(OBJS)

fclean: clean
	@$(MAKE) -C ./libft/. clean
	@rm -f $(NAME)
	@rm -f libft/libft.a

re: fclean $(NAME)

.PHONY: clean fclean re
