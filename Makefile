# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ohayek <ohayek@student.42istanbul.com.t    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/27 21:22:15 by ohayek            #+#    #+#              #
#    Updated: 2023/10/22 00:57:05 by ohayek           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = src/floor.c src/main.c src/mlx_init.c src/player.c src/raycast.c src/textures.c src/wall.c src/wall_2.c get_next_line/get_next_line.c get_next_line/get_next_line_utils.c
OBJ = $(SRC:.c=.o)
OBJ_BONUS = $(SRC_BONUS:.c=.o)


CC_FLAGS =
CC = gcc

MLX_FLAGS = -framework OpenGL -framework AppKit
MATH_FLAGS = -lm
MLX_LB	   = minilibx-linux/libmlx.a

LIBFT =libft/libft.a
NAME = cub3d
NAME_BONUS = fdf_bonus

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(MLX_LB)
	$(CC) $(CC_FLAGS) $(OBJ) $(LIBFT) $(MLX_LB) $(MATH_FLAGS) $(MLX_FLAGS) -o $@

$(LIBFT):
	make -C libft/ all
$(MLX_LB):
	make -C minilibx-linux/ all
	
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
	mv get_next_line.o get_next_line/
	mv get_next_line_utils.o get_next_line/

bonus: $(NAME_BONUS)

$(NAME_BONUS) : $(OBJ_BONUS) $(LIBFT) $(MLX_LB)
	$(CC) $(CC_FLAGS) $(MATH_FLAGS) $(MLX_FLAGS) $(OBJ_BONUS) $(LIBFT) $(MLX_LB) -o $(NAME_BONUS)

$(OBJ_BONUS): %.o: %.c
	$(CC) $(CC_FLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ) $(OBJ_BONUS)
	make -C libft/ clean
	make -C minilibx-linux/ clean
		
fclean: clean
	rm -rf $(NAME) $(NAME_BONUS)
	make -C libft/ fclean

re: fclean all