/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alix <alix@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 05:15:00 by aconstan          #+#    #+#             */
/*   Updated: 2025/06/05 23:13:16 by alix             ###   ########.fr       */
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

void loop_dda(t_config *conf, t_ray *ray)
{
    while (1)
    {
        // Step 1: Calcul des distances
        if (ray->side_dist_x < ray->side_dist_y) {
            ray->side_dist_x += ray->delta_dist_x;
            ray->map_x += ray->step_x;
            ray->side = 0;
        } else {
            ray->side_dist_y += ray->delta_dist_y;
            ray->map_y += ray->step_y;
            ray->side = 1;
        }

        // Step 2: Vérification des limites
        if (ray->map_x < 0 || ray->map_x >= conf->map.width ||
            ray->map_y < 0 || ray->map_y >= conf->map.height)
        {
            ray->hit = 1;
            ray->content = '1'; // Mur par défaut
            break;
        }

        // Step 3: Vérification du contenu
        char cell = conf->map.map[ray->map_y][ray->map_x];
        
        if (cell == '1') {
            ray->hit = 1;
            ray->content = '1';
            break;
        }
        else if (cell == 'C') {
            ray->hit = 1;
            ray->content = 'C';
            break;
        }
        else if (cell == '0') {
            continue; // Espace vide, continuer
        }
    }
}

double perform_dda(t_config *conf, t_ray *ray)
{
    // Vérifications initiales
    if (!conf || !ray || !conf->map.map || conf->map.width <= 0 || conf->map.height <= 0)
        return -1.0;

    // Initialisation des variables
    ray->delta_dist_x = (ray->ray_dir_x == 0) ? 1e30 : fabs(1 / ray->ray_dir_x);
    ray->delta_dist_y = (ray->ray_dir_y == 0) ? 1e30 : fabs(1 / ray->ray_dir_y);
    ray->hit = 0;
    ray->content = '0';

    // Boucle DDA sécurisée
    while (ray->hit == 0)
    {
        if (ray->side_dist_x < ray->side_dist_y) {
            ray->side_dist_x += ray->delta_dist_x;
            ray->map_x += ray->step_x;
            ray->side = 0;
        } else {
            ray->side_dist_y += ray->delta_dist_y;
            ray->map_y += ray->step_y;
            ray->side = 1;
        }

        // Vérification des limites de la carte
        if (ray->map_x < 0 || ray->map_x >= conf->map.width || 
            ray->map_y < 0 || ray->map_y >= conf->map.height)
        {
            ray->hit = 1;
            ray->content = '1';
            break;
        }

        // Lecture sécurisée de la cellule
        char cell = conf->map.map[ray->map_y][ray->map_x];
        if (cell == '1' || cell == 'C') {
            ray->hit = 1;
            ray->content = cell;
        }
    }

    // Calcul de la distance
    if (ray->side == 0)
        return (ray->map_x - conf->player.pos_x + (1 - ray->step_x) / 2) / ray->ray_dir_x;
    else
        return (ray->map_y - conf->player.pos_y + (1 - ray->step_y) / 2) / ray->ray_dir_y;
}
