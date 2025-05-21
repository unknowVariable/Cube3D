#include "cube3d.h"
// #include "mlx.h"

void	init_mlx(t_config *conf)
{
	int	w;
	int	h;

	conf->mlx.mlx_ptr = mlx_init();
	if (!conf->mlx.mlx_ptr)
		clean_exit(conf, "Erreur MLX");
	conf->mlx.win_ptr = mlx_new_window(conf->mlx.mlx_ptr, 1024, 768, "Cube3D");
	if (!conf->mlx.win_ptr)
		clean_exit(conf, "Erreur création fenêtre");
	conf->mlx.tex_no = mlx_xpm_file_to_image(conf->mlx.mlx_ptr, conf->no_path,
			&w, &h);
	if (!conf->mlx.tex_no)
		clean_exit(conf, "Erreur texture NO");
	conf->mlx.tex_so = mlx_xpm_file_to_image(conf->mlx.mlx_ptr, conf->so_path,
			&w, &h);
	if (!conf->mlx.tex_so)
		clean_exit(conf, "Erreur texture SO");
	conf->mlx.tex_we = mlx_xpm_file_to_image(conf->mlx.mlx_ptr, conf->we_path,
			&w, &h);
	if (!conf->mlx.tex_we)
		clean_exit(conf, "Erreur texture WE");
	conf->mlx.tex_ea = mlx_xpm_file_to_image(conf->mlx.mlx_ptr, conf->ea_path,
			&w, &h);
	if (!conf->mlx.tex_ea)
		clean_exit(conf, "Erreur texture EA");
}
