/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alix <alix@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 05:15:00 by aconstan          #+#    #+#             */
/*   Updated: 2025/06/04 20:09:26 by alix             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d_bonus.h"

void	toggle_nearby_doors(t_config *conf)
{
	int		i;
	int		px;
	int		py;
	t_door	*door;

	px = (int)conf->player.pos_x;
	py = (int)conf->player.pos_y;
	i = -1;
	while (++i < conf->door_count)
	{
		door = &conf->doors[i];
		if ((abs(door->x - px) <= 1 && (abs(door->y - py) <= 1))
		{
			door->is_open = !door->is_open;
			break ;
		}
	}
}