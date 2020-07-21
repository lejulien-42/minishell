# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lejulien <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/07/05 18:43:38 by lejulien          #+#    #+#              #
#    Updated: 2020/07/21 12:48:20 by frtalleu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = 	./srcs/main.c ./srcs/utils_0.c ./srcs/utils_1.c ./srcs/lst_to_str.c     \
	   	./srcs/utils_2.c ./srcs/shell_setup.c ./srcs/parse_helper.c             \
		./srcs/parser1.c ./srcs/parser2.c

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

re: fclean all

.PHONY: clean fclean re
