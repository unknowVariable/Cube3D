/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alix <alix@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 05:15:00 by aconstan          #+#    #+#             */
/*   Updated: 2025/05/23 07:45:08 by alix             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

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
	if (minimap_scale < 3) minimap_scale = 3; // Toujours au moins 3 px

	int minimap_height = map->height * minimap_scale;
	int origin_x = MINIMAP_MARGIN;
	int origin_y = img->height - minimap_height - MINIMAP_MARGIN;

	for (map_y = 0; map_y < map->height; map_y++)
	{
		for (map_x = 0; map_x < map->width; map_x++)
		{
			char cell = map->map[map_y][map_x];
			if (cell == '1')
				color = 0x00755428; // mur marron
			else if (cell == '0')
				color = 0x00EDD8B0; // sol beige
			else
				color = 0x00FFFFFF; // vide/blanc

			minimap_draw_square(img,
				origin_x + map_x * minimap_scale,
				origin_y + map_y * minimap_scale,
				color);
		}
	}

	// Curseur joueur (rouge)
	int cursor_radius = (minimap_scale < 6) ? 2 : 3;
	int px = origin_x + (int)(cfg->player.pos_x * minimap_scale);
	int py = origin_y + (int)(cfg->player.pos_y * minimap_scale);
	for (int i = -cursor_radius; i <= cursor_radius; i++)
		for (int j = -cursor_radius; j <= cursor_radius; j++)
			if ((i * i + j * j) <= cursor_radius * cursor_radius)
			{
				int x = px + i;
				int y = py + j;
				if (x >= 0 && x < img->width && y >= 0 && y < img->height)
				{
					char *dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
					*(unsigned int *)dst = 0x00FF2222;
				}
			}
}