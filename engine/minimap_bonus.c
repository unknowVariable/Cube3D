/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alix <alix@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 05:15:00 by aconstan          #+#    #+#             */
/*   Updated: 2025/05/23 09:33:45 by alix             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static void	put_pixel_to_img(t_img_data *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr;
	dst += y * img->line_len;
	dst += x * (img->bpp / 8);
	*(unsigned int *)dst = color;
}

static void	minimap_draw_square(t_img_data *img, t_ivec pos, int color)
{
	t_ivec	i;
	t_ivec	pixel;

	i.y = 0;
	while (i.y < MINIMAP_SCALE)
	{
		i.x = 0;
		while (i.x < MINIMAP_SCALE)
		{
			pixel.x = pos.x + i.x;
			pixel.y = pos.y + i.y;
			if (pixel.x >= 0 && pixel.x < img->width && pixel.y >= 0
				&& pixel.y < img->height)
				put_pixel_to_img(img, pixel.x, pixel.y, color);
			i.x++;
		}
		i.y++;
	}
}

static void	draw_minimap_content(t_config *cfg, t_ivec origin, int scale)
{
	t_ivec	map;
	int		color;

	map.y = 0;
	while (map.y < cfg->map.height)
	{
		map.x = 0;
		while (map.x < cfg->map.width)
		{
			if (cfg->map.map[map.y][map.x] == '1')
				color = 0x00755428;
			else if (cfg->map.map[map.y][map.x] == '0')
				color = 0x00EDD8B0;
			else
				color = 0x00FFFFFF;
			minimap_draw_square(&cfg->win, (t_ivec){origin.x + map.x * scale,
				origin.y + map.y * scale}, color);
			map.x++;
		}
		map.y++;
	}
}

static void	draw_player_indicator(t_config *cfg, t_ivec origin, int scale)
{
	t_ivec	i;
	t_ivec	center;
	int		radius;

	radius = 2;
	if (scale >= 6)
		radius = 3;
	center.x = origin.x + (int)(cfg->player.pos_x * scale);
	center.y = origin.y + (int)(cfg->player.pos_y * scale);
	i.y = -radius;
	while (i.y <= radius)
	{
		i.x = -radius;
		while (i.x <= radius)
		{
			if ((i.x * i.x + i.y * i.y) <= radius * radius && center.x
				+ i.x >= 0 && center.x + i.x < cfg->win.width && center.y
				+ i.y >= 0 && center.y + i.y < cfg->win.height)
				put_pixel_to_img(&cfg->win, center.x + i.x, center.y + i.y,
					0x00FF2222);
			i.x++;
		}
		i.y++;
	}
}

void	draw_minimap(t_config *cfg)
{
	int		scale;
	int		minimap_height;
	t_ivec	origin;

	scale = (cfg->win.width / 4) / cfg->map.width;
	if ((cfg->win.height / 4) / cfg->map.height < scale)
		scale = (cfg->win.height / 4) / cfg->map.height;
	if (scale < 3)
		scale = 3;
	minimap_height = cfg->map.height * scale;
	origin.x = MINIMAP_MARGIN;
	origin.y = cfg->win.height - minimap_height - MINIMAP_MARGIN;
	draw_minimap_content(cfg, origin, scale);
	draw_player_indicator(cfg, origin, scale);
}
