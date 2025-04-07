# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: samraoui <samraoui@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/23 16:35:33 by opdi-bia          #+#    #+#              #
#    Updated: 2025/04/07 15:55:28 by samraoui         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cube3d
CFLAGS = -Wall -Wextra -Werror -g3
SRCS = main.c\
	raycast.c\
	mooves.c\
	draw.c\
	utils.c ft_strtrim.c\
	get_next_line_utils.c\
	get_next_line.c\
	parsing.c\
	parsing2.c\
	parsing3.c\
	parsing4.c\
	read_map.c\
	read_map2.c\
	read_map3.c\
	textures.c\
	map_utils.c\
	colors.c\
	colors_utils.c\
	colors_utils2.c\
	utils_parsing.c\
	map_utils2.c\
	map_utils3.c\
	map_utils4.c\
	map_utils5.c\

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
