
NAME = cub3D
SRCS =  src/main.c \
		src/parsing/parsing.c \
		src/parsing/map_validation.c \
		src/objects/enemy/enemy.c \
		src/objects/player/player.c \
		src/objects/door/door.c \
		src/engine/create_map.c \
		src/engine/create_game.c \
		src/engine/map_free.c \
		src/engine/mouse_hooks.c \
		src/engine/map_generator.c \
		src/utils/get_next_line/get_next_line.c \
		src/utils/parsing_utils.c \
		src/utils/map_header_utils.c \
		src/utils/string_utils.c \
		src/utils/string_utils2.c \
		src/utils/map_init_utils.c \
		src/utils/map_utils.c \
		src/utils/map_utils2.c \
		src/utils/draw_utils.c \
		src/utils/math_utils.c \
		src/utils/rand_utils.c \
		src/utils/libft_utils.c \
		src/utils/time_utils.c \


OBJ_DIR = obj
OBJS = $(SRCS:src/%.c=$(OBJ_DIR)/%.o)
CC = cc
CFLAGS = -g -Wall -Wextra -Werror -Ofast
LIBMLX = -Llib/minilibx-linux -lmlx -lXext -lX11 -lm
INCLUDE = -Ilib/minilibx-linux -Ilib -Ilib

all: mlx $(NAME)

mlx:
	@make -C lib/minilibx-linux --no-print-directory

$(NAME): $(OBJS)
	@$(CC) $(OBJS) -o $(NAME) $(LIBMLX)
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

fclean: clean
	@rm -f $(NAME)
	@make -C lib/minilibx-linux clean --no-print-directory
	@echo "Executable deleted!"

re: fclean
	@echo "Recreating build directory..."
	@echo "Remaking executables..."
	@make --no-print-directory

r:
	make re && clear && ./cub3D maps/a.cub
v:
	make re && clear && valgrind --leak-check=full ./cub3D maps/a.cub

.PHONY: all mlx clean fclean re r v