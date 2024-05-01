# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kmiyazaw <kmiyazaw@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/26 13:38:25 by aeryilma          #+#    #+#              #
#    Updated: 2024/04/26 18:53:13 by kmiyazaw         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo

CC	= cc -g
CFLAGS	= -Wall -Wextra -Werror
#CFLAGS	+= -pthread -fsanitize=address
#CFLAGS	+= -pthread -fsanitize=thread
INCLUDE	= -Iinclude

SRC	= src/actions.c src/ft_utils.c src/init.c src/main.c src/monitor.c src/simu.c
OBJ	= $(SRC:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDE)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(INCLUDE) -o $(NAME)

clean:
	@rm -rf OBJ
	@echo "Objects Deleted"

fclean: clean
	@rm -rf philo
	@echo "Program Deleted"

re: fclean all

.PHONY: all clean fclean re
