/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene_bonus2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alix <alix@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 05:15:00 by aconstan          #+#    #+#             */
/*   Updated: 2025/06/02 15:51:53 by alix             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d_bonus.h"

int	get_floor_tex_color(t_config *conf, int y)
{
	double	current_dist;
	double	weight;
	double	floor_x;
	double	floor_y;
	int		tex_x;
	int		tex_y;

	current_dist = (double)WIN_HEIGHT / (2.0 * y - WIN_HEIGHT);
	weight = current_dist / conf->ray.perp_wall_dist;
	floor_x = weight * conf->ray.wall_x + (1.0 - weight) * conf->player.pos_x;
	floor_y = weight * conf->ray.wall_x + (1.0 - weight) * conf->player.pos_y;
	tex_x = (int)(floor_x * conf->floor_tex.width) % conf->floor_tex.width;
	tex_y = (int)(floor_y * conf->floor_tex.height) % conf->floor_tex.height;
	if (tex_x < 0)
		tex_x += conf->floor_tex.width;
	if (tex_y < 0)
		tex_y += conf->floor_tex.height;
	return (((int *)conf->floor_tex.addr)[conf->floor_tex.width * tex_y + tex_x]);
}

int	get_ceil_tex_color(t_config *conf, int y)
{
	double	current_dist;
	double	weight;
	double	floor_x;
	double	floor_y;
	int		tex_x;
	int		tex_y;

	current_dist = (double)WIN_HEIGHT / (2.0 * y - WIN_HEIGHT);
	weight = current_dist / conf->ray.perp_wall_dist;
	floor_x = weight * conf->ray.wall_x + (1.0 - weight) * conf->player.pos_x;
	floor_y = weight * conf->ray.wall_x + (1.0 - weight) * conf->player.pos_y;
	tex_x = (int)(floor_x * conf->ceil_tex.width) % conf->ceil_tex.width;
	tex_y = (int)(floor_y * conf->ceil_tex.height) % conf->ceil_tex.height;
	if (tex_x < 0)
		tex_x += conf->ceil_tex.width;
	if (tex_y < 0)
		tex_y += conf->ceil_tex.height;
	return (((int *)conf->ceil_tex.addr)[conf->ceil_tex.width * tex_y + tex_x]);
}