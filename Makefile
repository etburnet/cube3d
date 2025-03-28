# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/23 16:35:33 by opdi-bia          #+#    #+#              #
#    Updated: 2025/03/28 14:39:02 by eburnet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cube3d
CFLAGS = -Wall -Wextra -Werror -g3
SRCS = main.c\
	raycast.c\
	mooves.c draw.c\
	utils.c ft_strtrim.c\
	get_next_line_utils.c\
	get_next_line.c\
	parsing.c\
	read_map.c\
	textures.c\
	map_utils.c\
	colors.c\
	utils_parsing.c\

OBJS = $(SRCS:.c=.o)
CC = gcc
HEADERS = cube.h
MLX_PATH = ./minilibx-linux

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS) $(MLX_PATH)/libmlx.a
	@echo "Linking $@..."
	@$(CC) $(CFLAGS) $(OBJS) -L$(MLX_PATH) -lmlx -L/usr/lib -lXext -lX11 -lm -lz -o $(NAME)
	@echo "Executable $(NAME) created."
	
%.o: %.c $(HEADERS)
	@$(CC) $(CFLAGS) -I $(MLX_PATH) -O3 -c $< -o $@ >/dev/null
	
$(MLX_PATH)/libmlx.a:
	@echo "Building MiniLibX..."
	@make -C $(MLX_PATH) >/dev/null

clean :
	@echo "Cleaning object files..."
	@rm -f $(OBJS)
	@make -C $(MLX_PATH) clean >/dev/null
	@echo "Solong cleaned."

fclean :
	@echo "Cleaning all generated files..."
	@rm -f $(OBJS)
	@rm -f $(NAME)
	@make -C $(MLX_PATH) clean >/dev/null
	@echo "Solong Fcleaned."

re : fclean all
