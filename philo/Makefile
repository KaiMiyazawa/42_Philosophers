# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/26 13:38:25 by aeryilma          #+#    #+#              #
#    Updated: 2024/03/24 00:06:34 by kmiyazaw         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo

CC		= gcc -g
CFLAGS	= -pthread -Wall -Wextra -Werror -fsanitize=thread
INCLUDE	= -Iinclude

SRC		= $(shell find src -name "*.c")
OBJ		= $(SRC:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDE)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(INCLUDE) -o $(NAME)

clean:
	@find src -name "*.o" -delete
	@echo "Objects Deleted"

fclean: clean
	@rm -rf philo
	@echo "Program Deleted"

re: fclean all

.PHONY: all clean fclean re
