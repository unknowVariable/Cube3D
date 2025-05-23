/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alix <alix@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 05:15:00 by aconstan          #+#    #+#             */
/*   Updated: 2025/05/23 06:06:05 by alix             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static void	minimap_draw_square(t_img_data *img, int x, int y, int color)
{
	int i, j;
	for (i = 0; i < MINIMAP_SCALE; i++)
	{
		for (j = 0; j < MINIMAP_SCALE; j++)
		{
			int px = x + i;
			int py = y + j;
			if (px >= 0 && px < img->width && py >= 0 && py < img->height)
			{
				char *dst = img->addr + (py * img->line_len + px * (img->bpp / 8));
				*(unsigned int*)dst = color;
			}
		}
	}
}

void	draw_minimap(t_config *cfg)
{
	t_map_data	*map = &cfg->map;
	t_img_data	*img = &cfg->win;
	int			map_x, map_y;
	int			color;

    printf("minimap!\n");
	// Parcours de la map
	for (map_y = 0; map_y < map->height; map_y++)
	{
		for (map_x = 0; map_x < map->width; map_x++)
		{
			char cell = map->map[map_y][map_x];
			if (cell == '1')
				color = 0x00AAAAAA; // Mur : gris
			else if (cell == '0')
				color = 0x0033CC33; // Sol : vert
			else
				color = 0x00111111; // Inconnu/obstacle/autre : foncé

			minimap_draw_square(
				img,
				MINIMAP_MARGIN + map_x * MINIMAP_SCALE,
				MINIMAP_MARGIN + map_y * MINIMAP_SCALE,
				color
			);
		}
	}
	int px = MINIMAP_MARGIN + (int)(cfg->player.pos_x * MINIMAP_SCALE);
	int py = MINIMAP_MARGIN + (int)(cfg->player.pos_y * MINIMAP_SCALE);
	for (int i = -2; i <= 2; i++)
		for (int j = -2; j <= 2; j++)
			if ((i*i + j*j) <= 4)
			{
				int x = px + i;
				int y = py + j;
				if (x >= 0 && x < img->width && y >= 0 && y < img->height)
				{
					char *dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
					*(unsigned int*)dst = 0x00FF2222;
				}
			}
}