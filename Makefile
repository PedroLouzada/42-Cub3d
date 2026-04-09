# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pedro <pedro@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/04/09 19:05:36 by mrapp-he          #+#    #+#              #
#    Updated: 2026/04/09 22:09:09 by pedro            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = cub3D

SRCS =  src/main.c \
		src/parsing/parsing.c \
		src/parsing/map_validation.c \
		src/parsing/map_validation2.c \
		src/objects/enemy/enemy.c \
		src/objects/enemy/enemy_utils.c \
		src/objects/enemy/e_movement.c \
		src/objects/enemy/e_view.c \
		src/objects/player/player.c \
		src/objects/player/p_movement.c \
		src/objects/door/door.c \
		src/engine/map/create_map.c \
		src/engine/game/create_game.c \
		src/engine/game/alloc_assets.c \
		src/engine/controls/key_hooks.c \
		src/engine/draw/draw.c \
		src/engine/draw/draw1.c \
		src/engine/draw/draw2.c \
		src/engine/draw/draw3.c \
		src/engine/draw/draw4.c \
		src/engine/draw/draw5.c \
		src/engine/map/map_free.c \
		src/engine/controls/mouse_hooks.c \
		src/engine/map/map_generator.c \
		src/utils/get_next_line/get_next_line.c \
		src/parsing/parsing_utils.c \
		src/utils/map_utils/map_header_utils.c \
		src/utils/map_utils/map_header_utils2.c \
		src/utils/libft_utils/string_utils.c \
		src/utils/libft_utils/string_utils2.c \
		src/utils/map_utils/map_init_utils.c \
		src/utils/map_utils/map_utils.c \
		src/utils/map_utils/map_utils2.c \
		src/utils/math_utils.c \
		src/utils/rand_utils.c \
		src/utils/libft_utils/libft_utils.c \
		src/utils/time_utils.c \
		src/utils/exit.c \
		src/utils/libft_utils/split.c \
		src/engine/rays/raycasting.c \
		src/engine/rays/threads.c \

OBJ_DIR = obj
OBJS = $(SRCS:src/%.c=$(OBJ_DIR)/%.o)
CC = cc
CFLAGS = -g -Wall -Wextra -Werror #-fsanitize=thread
LIBMLX = -Llib/minilibx-linux -lmlx -lXext -lX11 -lm -lz
INCLUDE = -Ilib/minilibx-linux -Ilib/cub_headers -Ilib

all: mlx $(NAME)

mlx:
	@make -C lib/minilibx-linux --no-print-directory

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBMLX)
	@echo "Executable created!"

$(OBJ_DIR)/%.o: src/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	@if [ -d "$(OBJ_DIR)" ]; then \
		rm -rf $(OBJ_DIR); \
		echo "Build directory deleted!"; \
	else \
		echo "No build directory to delete!"; \
	fi
	rm -rf maps/level_1.cub; \
	rm -rf maps/level_2.cub; \
	rm -rf maps/level_3.cub; \
	rm -rf maps/level_4.cub; \
	rm -rf maps/level_5.cub; \

fclean: clean
	@rm -f $(NAME)
	@make -C lib/minilibx-linux clean --no-print-directory
	@echo "Executable deleted!"

re: fclean
	@echo "Recreating build directory..."
	@echo "Remaking executables..."
	@make --no-print-directory

r:
	make re && clear && ./cub3D maps/tutorial.cub
v:
	make re && clear && valgrind --track-fds=yes --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=x11.supp ./cub3D maps/a.cub

t:
	make re && clear && valgrind --tool=helgrind ./cub3D maps/a.cub

.PHONY: all mlx clean fclean re r v