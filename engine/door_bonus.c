/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alix <alix@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 05:15:00 by aconstan          #+#    #+#             */
/*   Updated: 2025/06/03 21:31:27 by alix             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d_bonus.h"

void    init_door_texture(t_config *conf)
{
    conf->door_tex.img = mlx_xpm_file_to_image(conf->mlx.mlx_ptr,
                        "textures/door.xpm",
                        &conf->door_tex.width,
                        &conf->door_tex.height);
    if (!conf->door_tex.img)
        clean_exit(conf, "Door texture load failed");
    
    conf->door_tex.addr = mlx_get_data_addr(conf->door_tex.img,
                          &conf->door_tex.bpp,
                          &conf->door_tex.line_len,
                          &conf->door_tex.endian);
}

void	handle_doors(t_config *conf, int map_x, int map_y, int *hit)
{
	t_door	*door;

	if (conf->map.map[map_y][map_x] == 'D')
	{
		door = get_door_at(conf, map_x, map_y);
		if (door && !door->is_open)
			*hit = 1;
	}
}

void	clean_doors(t_config *conf)
{
	if (conf->doors)
		free(conf->doors);
	if (conf->door_tex.img)
		mlx_destroy_image(conf->mlx.mlx_ptr, conf->door_tex.img);
}

