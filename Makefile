# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ohayek <ohayek@student.42istanbul.com.t    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/27 21:22:15 by ohayek            #+#    #+#              #
#    Updated: 2023/10/17 21:53:17 by ohayek           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = main.c
OBJ = $(SRC:.c=.o)
OBJ_BONUS = $(SRC_BONUS:.c=.o)


CC_FLAGS = -g
CC = gcc

MLX_FLAGS = -lXext -lX11 -lz
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