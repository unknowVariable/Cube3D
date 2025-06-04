NAME = cube3D

CC = cc
CFLAGS = -Wall -Wextra -Werror -I./header -I./mlx

MLX_DIR = ./mlx
MLX_LIB = $(MLX_DIR)/libmlx.a
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lbsd

SRCS = \
engine/dda.c \
engine/graphics.c \
engine/init_player.c \
engine/movement.c \
engine/render_scene.c \
engine/render_utils.c \
engine/windows_and_keys.c \
gnl/get_next_line.c \
parsing/check_file.c \
parsing/parse_content.c \
parsing/parse_map.c \
utils/exit_error.c \
utils/ft_atoi.c \
utils/ft_split.c \
utils/get_next_line_utils.c \
utils/global_utils1.c \
utils/global_utils2.c \
utils/global_utils3.c \
utils/parsingID_utils.c \
utils/parsingID_utils2.c \
utils/parsingMAP_utils.c \
utils/parsingMAP_utils2.c \
utils/parsingMAP_utils3.c \
main.c

SRCS_BONUS = \
engine/dda_bonus.c \
engine/graphics_bonus.c \
engine/init_player.c \
engine/movement.c \
engine/render_scene_bonus.c \
engine/render_scene_bonus2.c \
engine/render_utils.c \
engine/windows_and_keys.c \
engine/door_bonus.c \
engine/door_hook.c \
gnl/get_next_line.c \
parsing/check_file.c \
parsing/parse_content.c \
parsing/parse_map_bonus.c \
utils/exit_error.c \
utils/ft_atoi.c \
utils/ft_split.c \
utils/get_next_line_utils.c \
utils/global_utils1.c \
utils/global_utils2.c \
utils/global_utils3.c \
utils/parsingID_utils_bonus.c \
utils/parsingID_utils2.c \
utils/parsingMAP_utils.c \
utils/parsingMAP_utils2.c \
utils/parsingMAP_utils3_bonus.c \
utils/raycast_utils_bonus.c \
main_bonus.c

OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(MLX_LIB)
	$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAGS) -o $(NAME)

$(MLX_LIB):
	$(MAKE) -C $(MLX_DIR)

clean:
	rm -f $(OBJS) $(OBJS_BONUS)

fclean: clean
	rm -f $(NAME)

re: fclean all

bonus: $(OBJS_BONUS) $(MLX_LIB)
	$(CC) $(CFLAGS) $(OBJS_BONUS) $(MLX_FLAGS) -o $(NAME)

.PHONY: all clean fclean re bonus
