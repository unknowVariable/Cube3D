/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alix <alix@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 05:15:00 by aconstan          #+#    #+#             */
/*   Updated: 2025/06/04 20:00:29 by alix             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d_bonus.h"

void    handle_doors(t_config *conf, int map_x, int map_y, int *hit)
{
    t_door  *door;

    *hit = 0;
    if (conf->map.map[map_y][map_x] == 'D')
    {
        door = get_door_at(conf, map_x, map_y);
        if (door && !door->is_open)
            *hit = 1;
    }
}
void    clean_doors(t_config *conf)
{
    if (conf->doors) {
        free(conf->doors);
        conf->doors = NULL;
    }
    if (conf->door_tex.img) {
        mlx_destroy_image(conf->mlx.mlx_ptr, conf->door_tex.img);
        conf->door_tex.img = NULL;
    }
       mlx_destroy_image(conf->mlx.mlx_ptr, conf->door_tex.img);
}