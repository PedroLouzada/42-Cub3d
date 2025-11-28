
NAME = cub3D
SRCS = 
OBJ_DIR = build
OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)
CC = cc
CFLAGS = -g -Wall -Wextra -Werror -Ofast
LIBMLX = -Llib/mlx -lmlx -lXext -lX11 -lm
INCLUDE = -Ilib/mlx -Ilib

all: mlx $(NAME)

mlx:
	@make -C lib/minilibx-linux --no-print-directory

$(NAME): $(OBJS)
	@$(CC) $(OBJS) -o $(NAME) $(LIBMLX)
	@echo "Executable created!"

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)/src

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

.PHONY: all mlx clean fclean re
