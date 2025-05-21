#include "header/cube3d.h"

void	init_config(t_config *cfg)
{
	if (!cfg)
		return;
	cfg->no_path = NULL;
	cfg->so_path = NULL;
	cfg->we_path = NULL;
	cfg->ea_path = NULL;
	cfg->f_color = NULL;
	cfg->c_color = NULL;

	cfg->map.raw_lines = NULL;
	cfg->map.map = NULL;
	cfg->map.width = 0;
	cfg->map.height = 0;
	cfg->map.player_found = 0;
	cfg->map.player_x = 0;
	cfg->map.player_y = 0;
	cfg->map.player_dir = 0; 
}

int	main(int argc, char **argv)
{
	t_config	conf;
	int			fd;

	if (argc != 2 || !check_extension(argv[1]))
		ft_exit_error("Usage: ./cub3D <fichier.cub>");
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		ft_exit_error("Impossible d'ouvrir le fichier");
	ft_bzero(&conf, sizeof(t_config));
	init_config(&conf);
	parse_file(fd, &conf);
	close(fd);

	init_mlx(&conf);
	init_player(&conf);

	mlx_hook(conf.mlx.win_ptr, 17, 0, close_window, &conf);
	mlx_hook(conf.mlx.win_ptr, 2, 1L<<0, key_press, &conf);    // Key down (pressée)
mlx_hook(conf.mlx.win_ptr, 3, 1L<<1, key_release, &conf);  // Key up (relâchée)
mlx_loop_hook(conf.mlx.mlx_ptr, game_loop, &conf);   

	render_scene(&conf); // Affiche la première image
	mlx_loop(conf.mlx.mlx_ptr);

	return (0);
}