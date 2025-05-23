/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alix <alix@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 05:15:00 by aconstan          #+#    #+#             */
/*   Updated: 2025/05/23 08:15:06 by alix             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static void	draw_minimap_ray(t_img_data *img, int x0, int y0, int x1, int y1, int color)
{
	int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
	int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
	int err = dx + dy, e2;

	while (1)
	{
		if (x0 >= 0 && x0 < img->width && y0 >= 0 && y0 < img->height)
		{
			char *dst = img->addr + (y0 * img->line_len + x0 * (img->bpp / 8));
			*(unsigned int *)dst = color;
		}
		if (x0 == x1 && y0 == y1)
			break;
		e2 = 2 * err;
		if (e2 >= dy) { err += dy; x0 += sx; }
		if (e2 <= dx) { err += dx; y0 += sy; }
	}
}




#include <math.h> // pour cos/sin/M_PI

static void	draw_minimap_rays(t_config *cfg, int origin_x, int origin_y, int minimap_scale)
{
	double max_dist = 2.5;
	double fov = M_PI / 3.0; // 60 degrés
	double half_fov = fov / 2.0;
	int num_rays = 50; // nombre de rayons à tracer dans le cône

	for (int i = 0; i < num_rays; i++)
	{
		double ratio = (double)i / (num_rays - 1);
		double angle = -half_fov + ratio * fov;

		// direction du rayon avec rotation
		double dir_x = cfg->player.dir_x * cos(angle) - cfg->player.dir_y * sin(angle);
		double dir_y = cfg->player.dir_x * sin(angle) + cfg->player.dir_y * cos(angle);

		t_ray ray;
		ray.ray_dir_x = dir_x;
		ray.ray_dir_y = dir_y;
		ray.map_x = (int)cfg->player.pos_x;
		ray.map_y = (int)cfg->player.pos_y;
		ray.delta_x = (ray.ray_dir_x == 0) ? 1e30 : my_abs(1 / ray.ray_dir_x);
		ray.delta_y = (ray.ray_dir_y == 0) ? 1e30 : my_abs(1 / ray.ray_dir_y);

		double dist = perform_dda(cfg, &ray);
		if (dist > max_dist)
			dist = max_dist;

		double hit_x = cfg->player.pos_x + ray.ray_dir_x * dist;
		double hit_y = cfg->player.pos_y + ray.ray_dir_y * dist;

		int px = origin_x + (int)(cfg->player.pos_x * minimap_scale);
		int py = origin_y + (int)(cfg->player.pos_y * minimap_scale);
		int rx = origin_x + (int)(hit_x * minimap_scale);
		int ry = origin_y + (int)(hit_y * minimap_scale);

		draw_minimap_ray(&cfg->win, px, py, rx, ry, 0x00FFFFFF); // jaune clair
	}
}


static void	minimap_draw_square(t_img_data *img, int x, int y, int color)
{
	int		px;
	int		py;
	char	*dst;

	int i, j;
	for (i = 0; i < MINIMAP_SCALE; i++)
	{
		for (j = 0; j < MINIMAP_SCALE; j++)
		{
			px = x + i;
			py = y + j;
			if (px >= 0 && px < img->width && py >= 0 && py < img->height)
			{
				dst = img->addr + (py * img->line_len + px * (img->bpp / 8));
				*(unsigned int *)dst = color;
			}
		}
	}
}

void	draw_minimap(t_config *cfg)
{
	t_map_data *map = &cfg->map;
	t_img_data *img = &cfg->win;
	int map_x, map_y, color;

	int max_width = img->width / 4;
	int max_height = img->height / 4;
	int scale_x = max_width / map->width;
	int scale_y = max_height / map->height;
	int minimap_scale = (scale_x < scale_y) ? scale_x : scale_y;
	if (minimap_scale < 3) minimap_scale = 3;

	int minimap_height = map->height * minimap_scale;
	int origin_x = MINIMAP_MARGIN;
	int origin_y = img->height - minimap_height - MINIMAP_MARGIN;

	for (map_y = 0; map_y < map->height; map_y++)
	{
		for (map_x = 0; map_x < map->width; map_x++)
		{
			char cell = (map_x < (int)ft_strlen(map->map[map_y])) ? map->map[map_y][map_x] : ' ';
			if (cell == '1')
				color = 0x00755428; // mur marron
			else if (cell == '0' || ft_strchr("NESW", cell))
				color = 0x00EDD8B0; // sol beige
			else
				color = 0x00000000; // vide/blanc

			minimap_draw_square(img,
				origin_x + map_x * minimap_scale,
				origin_y + map_y * minimap_scale,
				color);
		}
	}

	// Curseur joueur ROUGE, carré plein et uniforme
	int cursor_radius = 3;
	int px = origin_x + (int)(cfg->player.pos_x * minimap_scale);
	int py = origin_y + (int)(cfg->player.pos_y * minimap_scale);

	for (int dy = -cursor_radius; dy <= cursor_radius; dy++)
	{
		for (int dx = -cursor_radius; dx <= cursor_radius; dx++)
		{
			if (dx * dx + dy * dy <= cursor_radius * cursor_radius)
			{
				int x = px + dx;
				int y = py + dy;
				if (x >= 0 && x < img->width && y >= 0 && y < img->height)
				{
					char *dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
					*(unsigned int *)dst = 0x00FF2222;
				}
			}
		}
	}
	draw_minimap_rays(cfg, origin_x, origin_y, minimap_scale);
}
