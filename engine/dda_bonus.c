/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alix <alix@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 05:15:00 by aconstan          #+#    #+#             */
/*   Updated: 2025/06/04 14:49:44 by alix             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d_bonus.h"

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

double perform_dda(t_config *conf, t_ray *ray)
{
    int hit = 0;
    t_door *door;

    while (!hit)
    {
        // 1. Vérifie d'abord les limites de la map
        if (ray->map_x < 0 || ray->map_x >= conf->map.width ||
            ray->map_y < 0 || ray->map_y >= conf->map.height)
        {
            hit = 1; // Sortie si hors limites
            break;
        }

        // 2. Logique DDA originale
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

        // 3. Vérifie le contenu de la case (SEULEMENT si dans les limites)
        if (ray->map_x >= 0 && ray->map_x < conf->map.width &&
            ray->map_y >= 0 && ray->map_y < conf->map.height)
        {
            if (conf->map.map[ray->map_y][ray->map_x] == 'D')
            {
                door = get_door_at(conf, ray->map_x, ray->map_y);
                if (door && !door->is_open)
                    hit = 1;
            }
            else if (conf->map.map[ray->map_y][ray->map_x] == '1')
                hit = 1;
        }
    }

    // Calcul de la distance
    if (ray->side == 0)
        return (ray->side_dist_x - ray->delta_x);
    else
        return (ray->side_dist_y - ray->delta_y);
}
