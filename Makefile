# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lejulien <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/07/05 18:43:38 by lejulien          #+#    #+#              #
#    Updated: 2020/07/11 21:38:08 by lejulien         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = ./srcs/main.c ./srcs/utils_0.c

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