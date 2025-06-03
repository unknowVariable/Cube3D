/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alix <alix@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 05:15:00 by aconstan          #+#    #+#             */
/*   Updated: 2025/06/03 19:53:25 by alix             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cube3d_bonus.h"

t_door	*get_door_at(t_config *conf, int x, int y)
{
	int	i;

	i = -1;
	while (++i < conf->door_count)
	{
		if (conf->doors[i].x == x && conf->doors[i].y == y)
			return (&conf->doors[i]);
	}
	return (NULL);
}

int	is_door_collision(t_config *conf, double x, double y)
{
	int		map_x;
	int		map_y;
	t_door	*door;

	map_x = (int)x;
	map_y = (int)y;
	if (conf->map.map[map_y][map_x] == 'D')
	{
		door = get_door_at(conf, map_x, map_y);
		if (door && !door->is_open)
			return (1);
	}
	return (0);
}