#ifndef CUBE3D_H
# define CUBE3D_H

# include "../mlx/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

#define WIN_WIDTH 1280
#define WIN_HEIGHT 720

#define KEY_W        13
#define KEY_S        1
#define KEY_A        0
#define KEY_D        2
#define KEY_LEFT     123
#define KEY_RIGHT    124
#define KEY_ESC      53

// Store the lines of the Map
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

// Stores Data relative to the MAP and player position
typedef struct s_map_data
{
	t_list			*raw_lines;
	char			**map;
	int				width;
	int				height;
	int				player_found;
	int				player_x;
	int				player_y;
	char			player_dir;
}					t_map_data;

// Structure de gestion graphique (MiniLibX)
typedef struct s_mlx
{
	void			*mlx_ptr;
	void			*win_ptr;
	void			*tex_no;
	void			*tex_so;
	void			*tex_we;
	void			*tex_ea;
}					t_mlx;

typedef struct s_player
{
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
	double			moveSpeed;
	double			rotSpeed;
}					t_player;

typedef struct s_config
{
	char			*no_path;
	char			*so_path;
	char			*we_path;
	char			*ea_path;
	char			*f_color;
	char			*c_color;

	t_map_data		map;
	t_mlx			mlx;
	t_player		player;
}					t_config;

// ** ENGINE ** //

/* Close_windows */
int					close_window(void *param);
int					handle_key(int keycode, void *param);

/* graphics */
void				init_mlx(t_config *conf);
/* init player */
void				init_player(t_config *c);

/* windows and keys */

/* Utils/utils.c */
int					ft_strlen(const char *str);
int					ft_strcmp(char *s1, char *s2);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strncpy(char *dest, char *src, unsigned int n);
int					ft_strncmp(char *s1, char *s2, unsigned int n);
char				*ft_strtrim(char const *s1, char const *set);
char				*ft_strdup(char *src);
int					is_only_spaces(char *line);

/* Error Exit */
void				ft_exit_error(char *msg);
void				free_list(t_list *lst);
void				free_paths_and_colors(t_config *c);
void				free_mlx_resources(t_config *c);
void				clean_exit(t_config *c, char *msg);

int					check_and_open_file(char *filename);
int					check_extension(char *filename);
void				parse_file(int fd, t_config *conf);
char				**ft_split(char const *s, char c);
void				ft_free_split(char **split);
int					ft_atoi(const char *str);
int					is_number(char *s);

/* Parse_map.c */
void				parse_map_lines(t_map_data *map, t_config *config, int fd,
						char *line);

/* Parsing Map utils */
int					is_player_char(char c);
int					is_map_char(char c);
t_list				*ft_lstnew(void *content);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				free_map(char **map);

/* Parsing Map utils 2 */
char				**list_to_tab(t_list *lines, int height, t_config *c);
int					is_border_void(char c);
int					is_player_or_floor(char c);
void				check_map_closed(char **map, int height, int width,
						t_config *c);

/* Parsing utils */
int					is_identifier(char *line);
int					all_identifiers_filled(t_config *conf);
void				set_config_field(t_config *conf, char *id, char *line);
int					is_valid_rgb(char *str);
int					parse_color_string_to_int(char *str, t_config *c);

/* Parsing utils 2 */
void				set_config_field(t_config *c, char *id, char *line);
int					store_path(t_config *c, char *id, char *v);
int					store_color(t_config *c, char *id, char *v);

/* Parsing utils 3 */
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memset(void *b, int c, size_t len);

/* GNL */
void				ft_bzero(void *s, size_t n);
void				*ft_calloc(size_t nmemb, size_t size);
char				*ft_strchr(const char *s, int c);
char				*get_next_line(int fd);

/* MLX */

void				init_mlx(t_config *conf);
int					close_window(void *param);

#endif
