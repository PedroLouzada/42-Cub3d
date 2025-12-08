
NAME = cub3D
# find all .c files under src
SRCS := $(shell find src -type f -name '*.c')
OBJ_DIR = build
# convert src/whatever.c -> build/src/whatever.o
OBJS := $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRCS))
CC = cc
CFLAGS = -g -Wall -Wextra -Werror -Ofast
LIBMLX = -Llib/minilibx-linux -lmlx -lXext -lX11 -lm
INCLUDE = -Ilib/minilibx-linux -Ilib

all: mlx $(NAME)

mlx:
	@make -C lib/minilibx-linux --no-print-directory

$(NAME): $(OBJS)
	@$(CC) $(OBJS) -o $(NAME) $(LIBMLX)
	@echo "Executable created!"

# compile: create the target directory for the object then compile
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

# note: object directories are created on-demand by the pattern rule above

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
