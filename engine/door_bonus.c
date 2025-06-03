/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alix <alix@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 05:15:00 by aconstan          #+#    #+#             */
/*   Updated: 2025/06/03 21:38:01 by alix             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d_bonus.h"

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

