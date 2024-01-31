# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/20 17:08:52 by miyazawa.ka       #+#    #+#              #
#    Updated: 2024/01/31 14:46:59 by miyazawa.ka      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# #SETUP
#NAME		=	philo
#CC			=	cc
##CFLAGS		=	-Wall -Wextra -Werror
#CFLAGS		=	-Wall -Wextra -Werror -fsanitize=address
#RM			=	rm -rf

## Component names
#LIBFT		= libft
#LIBFT_DIR	= $(LIBFT)
#LIBS		= $(LIBFT_DIR)/$(LIBFT).a

##FILES AND PATH
#HEADER_SRCS	=	philosophers.h
#HEADER_DIR	=	include/
#HEADER		=	$(addprefix $(HEADER_DIR), $(HEADER_SRCS))

#SRC	=	main.c ft_atoi.c
#SRC_DIR	=	src/
#PATH		=	$(addprefix $(PATH_DIR), $(PATH_SRC))
#OBJS		=	$(PATH:.c=.o)

##CHECKER_NAME=	checker
##BPATH_SRC	=
##BPATH_DIR	=	bonus/
##BPATH		=	$(addprefix $(BPATH_DIR), $(BPATH_SRC))
##OBJ_B		=	$(BPATH:.c=.o)

##COMMANDS
#$(LIBS):
#				@make -C $(LIBFT_DIR)

#%.o: %.c $(HEADER) $(LIBS)
#				@${CC} ${CFLAGS} $(HEADER)  -o $@ -c $<

#$(NAME):		$(OBJS)
#				@$(CC) ${CFLAGS} $(HEADER) $(OBJS) $(LIBS) -o $(NAME)
#				@echo -e "$(GREEN)$(NAME) created!$(DEFAULT)"

#all:			$(NAME)

##bonus:			$(OBJ_B)
##				@$(CC) ${CFLAGS} $(OBJ_B) -o $(CHECKER_NAME)
##				@echo -e "$(GREEN)$(CHECKER_NAME)(bonus) created!$(DEFAULT)"

#clean:
#				@$(RM) $(OBJS)
#				#@make clean -C $(LIBFT_DIR)/
#				@echo -e "$(YELLOW)object files deleted!$(DEFAULT)"

#fclean:			clean
#				@$(RM) $(NAME)
#				@make fclean -C $(LIBFT_DIR)/
#				@echo -e "$(RED)all deleted!$(DEFAULT)"

#re:				fclean all

#.PHONY:		all clean fclean bonus re

##COLORS
#RED = \033[1;31m
#GREEN = \033[1;32m
#YELLOW = \033[1;33m
#DEFAULT = \033[0m

# Product file
NAME			= philo

# Component names
LIBNAME			= libft

# Enumeration of files
SRC				=   main.c \
					game.c \
					show.c \
					opt.c  \
					init.c

# Enumeration of directories
SRCDIR			= ./src
INCDIR			= ./include
LIBDIR			= $(LIBNAME)
OBJDIR			= ./obj

# Macros to replace and/or integrate
SRCS			= $(addprefix $(SRCDIR)/, $(SRC))
OBJS			= $(addprefix $(OBJDIR)/, $(notdir $(SRCS:.c=.o)))
LIBS			= $(LIBDIR)/$(LIBNAME).a

# Aliases of commands
CC				= cc

# Command options (flags)
CFLAGS			= -Wall -Wextra -Werror -fsanitize=address
#CFLAGS			= -Wall -Wextra -Werror

INCLUDES		= -I$(INCDIR) -I$(LIBDIR)/$(LIBNAME).h
RMFLAGS			= -r

# Phonies
.PHONY: all clean fclean re

# Mandatory targets
all: $(LIBS) $(NAME)

clean:
	$(MAKE) clean -C $(LIBDIR)
	-$(RM) $(RMFLAGS) $(OBJDIR)

fclean:
	$(MAKE) fclean -C $(LIBDIR)
	-$(RM) $(RMFLAGS) $(OBJDIR)
	-$(RM) $(RMFLAGS) $(NAME)

re: fclean all

# Recipes
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LIBS) $(LDFLAGS) -o $(NAME)

$(LIBS):
	$(MAKE) -C $(LIBDIR)

$(OBJDIR):
	@mkdir -p $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<
