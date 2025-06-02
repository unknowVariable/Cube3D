/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alix <alix@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 05:15:00 by aconstan          #+#    #+#             */
/*   Updated: 2025/06/02 15:38:50 by alix             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d_bonus.h"

void load_floor_and_ceiling_textures(t_config *conf)
{
    conf->floor_tex.img = mlx_xpm_file_to_image(conf->mlx.mlx_ptr,
                                "textures/floor.xpm",
                                &conf->floor_tex.width, &conf->floor_tex.height);
    conf->floor_tex.addr = mlx_get_data_addr(conf->floor_tex.img,
                                &conf->floor_tex.bpp,
                                &conf->floor_tex.line_len,
                                &conf->floor_tex.endian);

    conf->ceil_tex.img = mlx_xpm_file_to_image(conf->mlx.mlx_ptr,
                                "textures/cell.xpm",
                                &conf->ceil_tex.width, &conf->ceil_tex.height);
    conf->ceil_tex.addr = mlx_get_data_addr(conf->ceil_tex.img,
                                &conf->ceil_tex.bpp,
                                &conf->ceil_tex.line_len,
                                &conf->ceil_tex.endian);
}

void	init_mlx(t_config *conf)
{
	conf->mlx.mlx_ptr = mlx_init();
	if (!conf->mlx.mlx_ptr)
		clean_exit(conf, "Erreur MLX");
	conf->mlx.win_ptr = mlx_new_window(conf->mlx.mlx_ptr, 640, 480, "Cube3D");
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
    load_floor_and_ceiling_textures(conf);
}
