# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/08 14:17:11 by hitran            #+#    #+#              #
#    Updated: 2024/08/20 00:19:34 by hitran           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler and flags
CC 				= cc
CFLAGS 			= -Wall -Wextra -Werror
MLX42_FLAGS		= -ldl -lglfw -pthread -lm
INCLUDES 		= -I./includes -I./mylib/includes -I./MLX42/include/MLX42
RM 				= rm -rf

# Directories
MYLIB_DIR	 	= ./mylib
MLX42_DIR		= ./MLX42
MAN_DIR 		= ./sources/mandatory
BONUS_DIR		= ./sources/bonus
MAP_DIR			= map
UTILS_DIR		= utils

# Source files by directory
MAN_FILES 		= 	start_solong.c 	read_map.c		utils.c  key_hook.c

MAN_SRCS		= 	main.c 	\
					$(addprefix $(MAN_DIR)/, $(MAN_FILES)) 
					
# Library
MYLIB 			= $(MYLIB_DIR)/mylib.a
MLX42			= $(MLX42_DIR)/build/libmlx42.a

# Executables
NAME 			= so_long

# Targets
all : $(NAME)

$(NAME): $(MYLIB) $(MLX42) $(MAN_SRCS)
	$(CC) $(CFLAGS) $(INCLUDES) $(MAN_SRCS) $(MYLIB) $(MLX42) $(MLX42_FLAGS) -o $(NAME)

$(MYLIB):
	$(MAKE) -C $(MYLIB_DIR)

$(MLX42): .mlx42
.mlx42: 
	@$(RM) $(MLX42_DIR)
	@git clone https://github.com/codam-coding-college/MLX42.git $(MLX42_DIR)
	@cd $(MLX42_DIR) && mkdir -p build && cd build && cmake .. && cmake --build . -j4
	@cd ..
	@$(RM) $(MLX42_DIR)/.git
	@touch .mlx42

clean:
	$(MAKE) clean -C $(MYLIB_DIR)
	$(RM) .bonus .mandatory $(MLX42_DIR)/build

fclean: clean
	$(MAKE) fclean -C $(MYLIB_DIR)
	$(RM) $(NAME) $(MLX42_DIR) .bonus .mandatory .mlx42
	
re: fclean all

.PHONY: all clean fclean re mandatory bonus