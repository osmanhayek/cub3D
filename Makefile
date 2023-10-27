# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ohayek <ohayek@student.42istanbul.com.t    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/27 21:22:15 by ohayek            #+#    #+#              #
#    Updated: 2023/10/24 16:40:29 by ohayek           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = src/floor.c src/main.c src/mlx_init.c src/player.c src/raycast.c src/textures.c src/wall.c src/wall_2.c get_next_line/get_next_line.c get_next_line/get_next_line_utils.c src/move.c src/parser.c\
	  src/parser1.c src/parser2.c src/parser3.c src/parser4.c
OBJ = $(SRC:.c=.o)


CC_FLAGS = -Wall -Wextra -Werror
CC = gcc

MLX_FLAGS = -framework OpenGL -framework AppKit
MATH_FLAGS = -lm
MLX_LB	   = minilibx/libmlx.a

LIBFT =libft/libft.a
NAME = cub3D

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(MLX_LB)
	$(CC) $(CC_FLAGS) $(OBJ) $(LIBFT) $(MLX_LB) $(MATH_FLAGS) $(MLX_FLAGS) -o $@

$(LIBFT):
	make -C libft/ all
$(MLX_LB):
	make -C minilibx/ all
	
$(OBJ): $(SRC) 
	$(CC) $(CC_FLAGS) -c $(SRC)
	mv floor.o src/
	mv main.o src/
	mv mlx_init.o src/
	mv player.o src/
	mv raycast.o src/
	mv textures.o src/
	mv wall_2.o src/
	mv wall.o src/
	mv move.o src/
	mv get_next_line.o get_next_line/
	mv get_next_line_utils.o get_next_line/
	mv parser.o src/
	mv parser1.o src/
	mv parser2.o src/
	mv parser3.o src/
	mv parser4.o src/

clean:
	rm -rf $(OBJ) $(OBJ_BONUS)
	make -C libft/ clean
	make -C minilibx/ clean
		
fclean: clean
	rm -rf $(NAME) $(NAME_BONUS)
	make -C libft/ fclean

re: fclean all
