/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alix <alix@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 05:15:00 by aconstan          #+#    #+#             */
/*   Updated: 2025/05/23 06:12:42 by alix             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	init_textures(t_config *conf)
{
	conf->mlx.tex_no.img = mlx_xpm_file_to_image(conf->mlx.mlx_ptr,
			conf->no_path, &conf->mlx.tex_no.width, &conf->mlx.tex_no.height);
	if (!conf->mlx.tex_no.img)
		clean_exit(conf, "Erreur texture NO");
	conf->mlx.tex_no.addr = mlx_get_data_addr(conf->mlx.tex_no.img,
			&conf->mlx.tex_no.bpp, &conf->mlx.tex_no.line_len,
			&conf->mlx.tex_no.endian);
	conf->mlx.tex_so.img = mlx_xpm_file_to_image(conf->mlx.mlx_ptr,
			conf->so_path, &conf->mlx.tex_so.width, &conf->mlx.tex_so.height);
	if (!conf->mlx.tex_so.img)
		clean_exit(conf, "Erreur texture SO");
	conf->mlx.tex_so.addr = mlx_get_data_addr(conf->mlx.tex_so.img,
			&conf->mlx.tex_so.bpp, &conf->mlx.tex_so.line_len,
			&conf->mlx.tex_so.endian);
	conf->mlx.tex_we.img = mlx_xpm_file_to_image(conf->mlx.mlx_ptr,
			conf->we_path, &conf->mlx.tex_we.width, &conf->mlx.tex_we.height);
	if (!conf->mlx.tex_we.img)
		clean_exit(conf, "Erreur texture WE");
	conf->mlx.tex_we.addr = mlx_get_data_addr(conf->mlx.tex_we.img,
			&conf->mlx.tex_we.bpp, &conf->mlx.tex_we.line_len,
			&conf->mlx.tex_we.endian);
	conf->mlx.tex_ea.img = mlx_xpm_file_to_image(conf->mlx.mlx_ptr,
			conf->ea_path, &conf->mlx.tex_ea.width, &conf->mlx.tex_ea.height);
	if (!conf->mlx.tex_ea.img)
		clean_exit(conf, "Erreur texture EA");
	conf->mlx.tex_ea.addr = mlx_get_data_addr(conf->mlx.tex_ea.img,
			&conf->mlx.tex_ea.bpp, &conf->mlx.tex_ea.line_len,
			&conf->mlx.tex_ea.endian);
}

void	init_mlx(t_config *conf)
{
	conf->mlx.mlx_ptr = mlx_init();
	if (!conf->mlx.mlx_ptr)
		clean_exit(conf, "Erreur MLX");
	conf->mlx.win_ptr = mlx_new_window(conf->mlx.mlx_ptr, WIN_WIDTH, WIN_HEIGHT,
			"Cube3D");
	if (!conf->mlx.win_ptr)
		clean_exit(conf, "Erreur création fenêtre");
	init_textures(conf);
}
