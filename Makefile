# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/08 14:17:11 by hitran            #+#    #+#              #
#    Updated: 2024/08/11 19:41:07 by hitran           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler and flags
CC 				= cc
CFLAGS 			= -Wall -Wextra -Werror
INCLUDES 		= -I./includes -I./mylib/includes
RM 				= rm -f

# Directories
MYLIB_DIR	 	= ./mylib
MLX42_DIR		= ./MLX42
MAN_DIR 		= ./sources/mandatory
BONUS_DIR		= ./sources/bonus
MAP_DIR			= ./sources/map
UTILS_DIR		= ./sources/utils

# Source files by directory
MAP_FILES 		= 	read_map.c				validate_map.c		

UTILS_FILES		= 	handle_errors.c

MAN_SRCS		= 	main.c 	\
					$(addprefix $(MAP_DIR)/, $(MAP_FILES)) \
					$(addprefix $(UTILS_DIR)/, $(UTILS_FILES))
					
# Library
MYLIB 			= $(MYLIB_DIR)/mylib.a

# Executables
NAME 			= so_long

# Targets
all : $(NAME)

$(NAME): $(MYLIB) $(MAN_SRCS)
	$(CC) $(CFLAGS) $(INCLUDES) $(MAN_SRCS) $(MYLIB) -o $(NAME)

$(MYLIB):
	$(MAKE) -C $(MYLIB_DIR)

clean:
	$(MAKE) clean -C $(MYLIB_DIR)
	$(RM) .bonus .mandatory


fclean: clean
	$(MAKE) fclean -C $(MYLIB_DIR)
	$(RM) $(NAME) .bonus .mandatory
	
re: fclean all

.PHONY: all clean fclean re mandatory bonus