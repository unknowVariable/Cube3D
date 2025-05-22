/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alix <alix@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 05:15:00 by aconstan          #+#    #+#             */
/*   Updated: 2025/05/22 22:15:03 by alix             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

double	my_abs(double x)
{
	if (x < 0)
		return (-x);
	return (x);
}

void	init_dda_step_x(t_config *conf, t_ray *ray)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (conf->player.pos_x - ray->map_x) * ray->delta_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - conf->player.pos_x)
			* ray->delta_x;
	}
}

void	init_dda_step_y(t_config *conf, t_ray *ray)
{
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (conf->player.pos_y - ray->map_y) * ray->delta_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - conf->player.pos_y)
			* ray->delta_y;
	}
}

void	loop_dda(t_config *conf, t_ray *ray)
{
	while (conf->map.map[ray->map_y][ray->map_x] != '1')
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
	}
}

double	perform_dda(t_config *conf, t_ray *ray)
{
	init_dda_step_x(conf, ray);
	init_dda_step_y(conf, ray);
	loop_dda(conf, ray);
	if (ray->side == 0)
		return (ray->side_dist_x - ray->delta_x);
	return (ray->side_dist_y - ray->delta_y);
}
