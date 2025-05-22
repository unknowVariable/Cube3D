#include "cube3d.h"

// #include "mlx.h"

void	init_mlx(t_config *conf)
{
	conf->mlx.mlx_ptr = mlx_init();
	if (!conf->mlx.mlx_ptr)
		clean_exit(conf, "Erreur MLX");
	conf->mlx.win_ptr = mlx_new_window(conf->mlx.mlx_ptr, 1024, 768, "Cube3D");
	if (!conf->mlx.win_ptr)
		clean_exit(conf, "Erreur création fenêtre");
	conf->mlx.tex_no.img = mlx_xpm_file_to_image(conf->mlx.mlx_ptr,
			conf->no_path, &conf->mlx.tex_no.width, &conf->mlx.tex_no.height);
	if (!conf->mlx.tex_no.img)
		clean_exit(conf, "Erreur texture NO");
	conf->mlx.tex_so.img = mlx_xpm_file_to_image(conf->mlx.mlx_ptr,
			conf->so_path, &conf->mlx.tex_so.width, &conf->mlx.tex_so.height);
	if (!conf->mlx.tex_so.img)
		clean_exit(conf, "Erreur texture SO");
	conf->mlx.tex_we.img = mlx_xpm_file_to_image(conf->mlx.mlx_ptr,
			conf->we_path, &conf->mlx.tex_we.width, &conf->mlx.tex_we.height);
	if (!conf->mlx.tex_we.img)
		clean_exit(conf, "Erreur texture WE");
	conf->mlx.tex_ea.img = mlx_xpm_file_to_image(conf->mlx.mlx_ptr,
			conf->ea_path, &conf->mlx.tex_ea.width, &conf->mlx.tex_ea.height);
	if (!conf->mlx.tex_ea.img)
		clean_exit(conf, "Erreur texture EA");
}
