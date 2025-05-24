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

void	init_minimap_ray(t_config *conf, t_ray *ray, double cam_x)
{
	ray->ray_dir_x = conf->player.dir_x + conf->player.plane_x * cam_x;
	ray->ray_dir_y = conf->player.dir_y + conf->player.plane_y * cam_x;
	if (ray->ray_dir_x == 0)
		ray->delta_x = 1e30;
	else
		ray->delta_x = my_abs(1 / ray->ray_dir_x);
	if (ray->ray_dir_y == 0)
		ray->delta_y = 1e30;
	else
		ray->delta_y = my_abs(1 / ray->ray_dir_y);
}

void	draw_minimap_rays(t_config *cfg, int origin_x, int origin_y, int scale)
{
	t_ray	ray;
	int		i;
	double	cam_x;
	double	hit_x;
	double	hit_y;
	int		px;
	int		py;
	int		rx;
	int		ry;

	i = 0;
	while (i < 40)
	{
		cam_x = 2.0 * i / 40.0 - 1.0;
		init_minimap_ray(cfg, &ray, cam_x);
		ray.map_x = (int)cfg->player.pos_x;
		ray.map_y = (int)cfg->player.pos_y;
		ray.perp_wall_dist = perform_dda(cfg, &ray);
		hit_x = cfg->player.pos_x + ray.ray_dir_x * ray.perp_wall_dist;
		hit_y = cfg->player.pos_y + ray.ray_dir_y * ray.perp_wall_dist;
		px = origin_x + (int)(cfg->player.pos_x * scale);
		py = origin_y + (int)(cfg->player.pos_y * scale);
		rx = origin_x + (int)(hit_x * scale);
		ry = origin_y + (int)(hit_y * scale);
		draw_minimap_ray(&cfg->win, px, py, rx, ry, COLOR_CUIVRE);
		i++;
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


typedef struct s_minimap
{
	int	scale;
	int	origin_x;
	int	origin_y;
	int	cursor_px;
	int	cursor_py;
}		t_minimap;

static int	get_minimap_scale(t_img_data *img, t_map_data *map)
{
	int	max_width;
	int	max_height;
	int	scale_x;
	int	scale_y;
	int	scale;

	max_width = img->width / 4;
	max_height = img->height / 4;
	scale_x = max_width / map->width;
	scale_y = max_height / map->height;
	if (scale_x < scale_y)
		scale = scale_x;
	else
		scale = scale_y;
	if (scale < 3)
		scale = 3;
	return (scale);
}

static void	draw_minimap_player(t_img_data *img, t_minimap *mmap, int radius)
{
	int	dx;
	int	dy;
	int	x;
	int	y;
	char	*dst;

	dy = -radius;
	while (dy <= radius)
	{
		dx = -radius;
		while (dx <= radius)
		{
			if (dx * dx + dy * dy <= radius * radius)
			{
				x = mmap->cursor_px + dx;
				y = mmap->cursor_py + dy;
				if (x >= 0 && x < img->width && y >= 0 && y < img->height)
				{
					dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
					*(unsigned int *)dst = 0x00FF2222;
				}
			}
			dx++;
		}
		dy++;
	}
}

void	draw_minimap(t_config *cfg)
{
	t_map_data	*map;
	t_img_data	*img;
	t_minimap	mmap;
	int			map_x;
	int			map_y;
	int			color;
	char		cell;

	map = &cfg->map;
	img = &cfg->win;
	mmap.scale = get_minimap_scale(img, map);
	mmap.origin_x = MINIMAP_MARGIN;
	mmap.origin_y = img->height - (map->height * mmap.scale) - MINIMAP_MARGIN;
	mmap.cursor_px = mmap.origin_x + (int)(cfg->player.pos_x * mmap.scale);
	mmap.cursor_py = mmap.origin_y + (int)(cfg->player.pos_y * mmap.scale);

	map_y = 0;
	while (map_y < map->height)
	{
		map_x = 0;
		while (map_x < map->width)
		{
			if (map_x < (int)ft_strlen(map->map[map_y]))
				cell = map->map[map_y][map_x];
			else
				cell = ' ';
			if (cell == '1')
				color = COLOR_DARK_BROWN;
			else if (cell == '0' || ft_strchr("NESW", cell))
				color = COLOR_BEIGE_CLAIR;
			else
				color = COLOR_TETE_BRULEE;
			minimap_draw_square(img,
				mmap.origin_x + map_x * mmap.scale,
				mmap.origin_y + map_y * mmap.scale,
				color);
			map_x++;
		}
		map_y++;
	}
	draw_minimap_player(img, &mmap, 3);
	draw_minimap_rays(cfg, mmap.origin_x, mmap.origin_y, mmap.scale);
}

