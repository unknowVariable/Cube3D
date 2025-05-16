# Nom de l'exécutable
NAME = cube3D

# Compilateur et flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -I./header/ -I./mlx

# MiniLibX Linux
MLX_DIR = ./mlx
MLX_LIB = $(MLX_DIR)/libmlx.a
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lbsd

OBJS_DIR = obj
# Fichiers source (hors mlx)
SRCS = $(shell find . -type f -name '*.c' ! -path "./mlx/*")
OBJS = $(SRCS:./%.c=$(OBJS_DIR)/%.o)

# Règles
all: $(NAME)

$(NAME): $(OBJS) $(MLX_LIB)
	$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAGS) -o $(NAME)

$(OBJS_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ 

$(MLX_LIB):
	$(MAKE) -C $(MLX_DIR)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
