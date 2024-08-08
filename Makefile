# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/08 14:17:11 by hitran            #+#    #+#              #
#    Updated: 2024/08/08 14:17:13 by hitran           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler and flags
CC 				= cc
CFLAGS 			= -Wall -Wextra -Werror
INCLUDES 		= -I./includes -I./mylib/includes
RM 				= rm -f

# Directories
MAN_DIR 		= ./sources/mandatory
BONUS_DIR		= ./sources/bonus
MYLIB_DIR	 	= ./mylib
MLX42_DIR		= ./MLX42

# Source files by directory
MAN_FILES 		= 	
					
BONUS_FILES 	= 	

MAN_SRCS		= 	main.c $(addprefix $(MAN_DIR)/, $(MAN_FILES))

BONUS_SRCS		=	main_bonus.c $(addprefix $(BONUS_DIR)/, $(BONUS_FILES))
					
# Library
MYLIB 			= $(MYLIB_DIR)/mylib.a

# Executables
NAME 			= so_long

# Targets
all : mandatory

mandatory : .mandatory
.mandatory: $(MYLIB) $(MAN_SRCS)
	$(CC) $(CFLAGS) $(INCLUDES) $(MAN_SRCS) $(MYLIB) -o $(NAME)
	@touch .mandatory
	@$(RM) .bonus

bonus: .bonus
.bonus: $(MYLIB) $(BONUS_SRCS)
	$(CC) $(CFLAGS) $(INCLUDES) $(BONUS_SRCS) $(MYLIB) -o $(NAME)
	@touch .bonus
	@$(RM) .mandatory

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