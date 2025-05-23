/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alix <alix@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 05:15:00 by aconstan          #+#    #+#             */
/*   Updated: 2025/05/22 22:29:32 by alix             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static void	set_north(t_config *c)
{
	c->player.dir_x = 0;
	c->player.dir_y = -1;
	c->player.plane_x = 0.66;
	c->player.plane_y = 0;
}

static void	set_south(t_config *c)
{
	c->player.dir_x = 0;
	c->player.dir_y = 1;
	c->player.plane_x = -0.66;
	c->player.plane_y = 0;
}

static void	set_east(t_config *c)
{
	c->player.dir_x = 1;
	c->player.dir_y = 0;
	c->player.plane_x = 0;
	c->player.plane_y = 0.66;
}

static void	set_west(t_config *c)
{
	c->player.dir_x = -1;
	c->player.dir_y = 0;
	c->player.plane_x = 0;
	c->player.plane_y = -0.66;
}

void	init_player(t_config *c)
{
	c->player.pos_x = c->map.player_x + 0.5;
	c->player.pos_y = c->map.player_y + 0.5;
	if (c->map.player_dir == 'N')
		set_north(c);
	else if (c->map.player_dir == 'S')
		set_south(c);
	else if (c->map.player_dir == 'E')
		set_east(c);
	else if (c->map.player_dir == 'W')
		set_west(c);
}
