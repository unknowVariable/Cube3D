/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alix <alix@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 05:15:00 by aconstan          #+#    #+#             */
/*   Updated: 2025/06/05 23:05:32 by alix             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_BONUS_H
# define CUBE3D_BONUS_H

# include "mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# define WIN_WIDTH 1280
# define WIN_HEIGHT 720
# define TEX_WIDTH 128
# define TEX_HEIGHT 128
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_ESC 65307
# define KEY_1 65436
# define KEY_2 65433
# define KEY_3 65435
# define SPEED_1 0.010
# define SPEED_2 0.020
# define SPEED_3 0.030
# define MOUSESENSITIVITY 0.01
# define COIN_ANIM_FRAMES 6
# define COIN_ANIM_SPEED 12

// Store the lines of the Map
typedef struct s_list
{
	void				*content;
	struct s_list		*next;
}
						t_list;
typedef struct s_map_coin
{
	int					x;
	int					y;
	int					collected;
	struct s_map_coin	*next;
}						t_map_coin;

// Stores Data relative to the MAP and player position
typedef struct s_map_data
{
	t_list				*raw_lines;
	char				**map;
	int					width;
	int					height;
	int					player_found;
	int					player_x;
	int					player_y;
	char				player_dir;
	t_map_coin			*coins;
	int					coin_count;
}						t_map_data;

typedef struct s_ray
{
    double              camera_x;
    int                 map_x;
    int                 map_y;
    double              ray_dir_x;
    double              ray_dir_y;
    double              delta_x;       // Renommez en delta_dist_x pour cohérence
    double              delta_y;       // Renommez en delta_dist_y pour cohérence
    double              side_dist_x;
    double              side_dist_y;
    int                 side;
    int                 line_height;
    int                 step_x;
    int                 step_y;
    int                 draw_start;
    int                 draw_end;
    double              perp_wall_dist;
    double              wall_x;
    // Ajoutez ces nouveaux champs
    double              delta_dist_x;  // Nouveau
    double              delta_dist_y;  // Nouveau
    int                 hit;           // Nouveau
    char                content;       // Nouveau ('1', 'C', etc.)
}                       t_ray;
typedef struct s_img_data
{
	void				*img;
	char				*addr;
	int					width;
	int					height;
	int					bpp;
	int					line_len;
	int					endian;
	int					x;
	int					y;
	double				tex_pos;
}						t_img_data;

// Structure de gestion graphique (MiniLibX)
typedef struct s_mlx
{
	void				*mlx_ptr;
	void				*win_ptr;
	t_img_data			tex_no;
	t_img_data			tex_so;
	t_img_data			tex_we;
	t_img_data			tex_ea;
}						t_mlx;

typedef struct s_player
{
	double				pos_x;
	double				pos_y;
	double				dir_x;
	double				dir_y;
	double				plane_x;
	double				plane_y;
}						t_player;

typedef struct s_coin_anim
{
	void				*img[COIN_ANIM_FRAMES];
	int					frame;
	int					width;
	int					height;
}						t_coin_anim;

typedef struct s_coin_draw
{
	char				*src_addr;
	int					bpp;
	int					size_line;
	int					pos_x;
	int					pos_y;
}						t_coin_draw;


typedef struct s_config
{
	char				*no_path;
	char				*so_path;
	char				*we_path;
	char				*ea_path;
	int					f_color;
	int					c_color;
	int					keys[70000];
	double				move_speed;
	double				rot_speed;
	t_map_data			map;
	t_mlx				mlx;
	t_player			player;
	t_img_data			win;
	t_ray				ray;
	t_img_data			floor_tex;
	t_img_data			ceil_tex;
	t_coin_anim			coin;
}						t_config;

// ** ENGINE ** //

void					free_floor_and_ceiling(t_config *c);
void					free_coin_images(t_config *c);
/* coin */
void					load_coin_anim(t_config *cfg);
void					draw_coin_anim(t_config *cfg);
void					display_coins(void *mlx, void *win, int coins);
void					put_coin_with_transparency(t_config *cfg, int frame,
							int pos_x, int pos_y);
void					set_coin_filenames(char **filenames);
void					load_coin_anim(t_config *cfg);
int						should_draw_coin_pixel(int color);
void					add_map_coin(t_map_data *map, int x, int y);

int						get_tex_coord(int size, double f);
int						get_tex_color_at(t_img_data *tex, double fx, double fy);
void					get_floor_wall_xy(t_config *conf, double *wx,
							double *wy);
void					draw_ceiling_column(t_config *conf, int end, double wx,
							double wy);
void					draw_floor_column(t_config *conf, int start, double wx,
							double wy);
void					draw_column(t_config *conf, t_img_data tex_img);

int						mouse_move(int x, int y, void *param);

/* handle_key */
int						key_press(int key, void *param);
int						key_release(int key, void *param);
int						game_loop(void *param);

/* movement.c*/
void					move_forward(t_config *conf, double speed);
void					move_backward(t_config *conf, double speed);
void					strafe_left(t_config *conf, double speed);
void					strafe_right(t_config *conf, double speed);
void					rotate_view(t_config *conf, double rot);

// --- Prototypes raycasting ---
void					render_scene(t_config *conf);
double					perform_dda(t_config *conf, t_ray *ray);
double					my_abs(double x);
void					put_pixel(t_config *conf, int y, int color);

/* Close_windows */
int						close_window(void *param);
int						handle_key(int keycode, void *param);

/* graphics */
void					init_mlx(t_config *conf);
/* init player */
void					init_player(t_config *c);

/* windows and keys */

/* Utils/utils.c */
int						ft_strlen(const char *str);
int						ft_strcmp(char *s1, char *s2);
char					*ft_strjoin(char const *s1, char const *s2);
char					*ft_strncpy(char *dest, char *src, unsigned int n);
int						ft_strncmp(char *s1, char *s2, unsigned int n);
char					*ft_strtrim(char const *s1, char const *set);
char					*ft_strdup(char *src);
int						is_only_spaces(char *line);

/* Error Exit */
void					ft_exit_error(char *msg);
void					free_list(t_list *lst);
void					free_paths_and_colors(t_config *c);
void					free_mlx_resources(t_config *c);
void					clean_exit(t_config *c, char *msg);

int						check_and_open_file(char *filename);
int						check_extension(char *filename);
void					parse_file(int fd, t_config *conf);
char					**ft_split(char const *s, char c);
void					ft_free_split(char **split);
int						ft_atoi(const char *str);
int						is_number(char *s);

/* Parse_map.c */
void					parse_map_lines(t_map_data *map, t_config *config,
							int fd, char *line);

/* Parsing Map utils */
int						is_player_char(char c);
int						is_map_char(char c);
t_list					*ft_lstnew(void *content);
void					ft_lstadd_back(t_list **lst, t_list *new);
void					free_map(char **map);

/* Parsing Map utils 2 */
char					**list_to_tab(t_list *lines, int height, t_config *c);
int						is_border_void(char c);
int						is_player_or_floor(char c);
void					check_map_closed(char **map, int height, int width,
							t_config *c);

/* Parsing Map utils 3 */
void					clean_and_exit(t_config *cfg, char *s1, char *s2,
							char *msg);
void					create_padded_line(t_map_data *map, char *trimmed);

/* Parsing utils */
int						is_identifier(char *line);
int						all_identifiers_filled(t_config *conf);
void					set_config_field(t_config *conf, char *id, char *line);
int						is_valid_rgb(char *str);
int						parse_color_string_to_int(char *str, t_config *c);

/* Parsing utils 2 */
void					set_config_field(t_config *c, char *id, char *line);
int						store_path(t_config *c, char *id, char *v);
int						store_color(t_config *c, char *id, char *v);

/* Parsing utils 3 */
void					*ft_memcpy(void *dst, const void *src, size_t n);
void					*ft_memset(void *b, int c, size_t len);

/* GNL */
void					ft_bzero(void *s, size_t n);
void					*ft_calloc(size_t nmemb, size_t size);
char					*ft_strchr(const char *s, int c);
char					*get_next_line(int fd);

/* MLX */

void					init_mlx(t_config *conf);
int						close_window(void *param);

#endif
