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

static void	bresenham_init(t_minimap *mmap, int *err)
{
	mmap->delta_x = abs(mmap->hit_px - mmap->player_x);
	mmap->delta_y = -abs(mmap->hit_py - mmap->player_y);
	*err = mmap->delta_x + mmap->delta_y;
	if (mmap->player_x < mmap->hit_px)
		mmap->step_x = 1;
	else
		mmap->step_x = -1;
	if (mmap->player_y < mmap->hit_py)
		mmap->step_y = 1;
	else
		mmap->step_y = -1;
}

static void	ray_pixel_put(t_img_data *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	draw_minimap_ray(t_img_data *img, t_minimap *mmap, int color)
{
	int	err;
	int	e2;

	bresenham_init(mmap, &err);
	while (mmap->player_x != mmap->hit_px || mmap->player_y != mmap->hit_py)
	{
		ray_pixel_put(img, mmap->player_x, mmap->player_y, color);
		e2 = 2 * err;
		if (e2 >= mmap->delta_y)
		{
			err += mmap->delta_y;
			mmap->player_x += mmap->step_x;
		}
		if (e2 <= mmap->delta_x)
		{
			err += mmap->delta_x;
			mmap->player_y += mmap->step_y;
		}
	}
	ray_pixel_put(img, mmap->hit_px, mmap->hit_py, color);
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
	t_ray		ray;
	t_minimap	mmap;
	int			i;
	double		cam_x;

	i = 0;
	while (i < 40)
	{
		cam_x = 2.0 * i / 40.0 - 1.0;
		init_minimap_ray(cfg, &ray, cam_x);
		ray.map_x = (int)cfg->player.pos_x;
		ray.map_y = (int)cfg->player.pos_y;
		ray.perp_wall_dist = perform_dda(cfg, &ray);
		mmap.player_x = origin_x + (int)(cfg->player.pos_x * scale);
		mmap.player_y = origin_y + (int)(cfg->player.pos_y * scale);
		mmap.hit_px = origin_x + (int)((cfg->player.pos_x + ray.ray_dir_x
					* ray.perp_wall_dist) * scale);
		mmap.hit_py = origin_y + (int)((cfg->player.pos_y + ray.ray_dir_y
					* ray.perp_wall_dist) * scale);
		draw_minimap_ray(&cfg->win, &mmap, COLOR_CUIVRE);
		i++;
	}
}

static void	minimap_draw_square(t_img_data *img, int x, int y, int color)
{
	int		px;
	int		py;
	char	*dst;
	int		i;
	int		j;

	i = -1;
	while (++i < MINIMAP_SCALE)
	{
		j = -1;
		while (++j < MINIMAP_SCALE)
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
	char	*dst;

	mmap->y = -radius - 1;
	while (++mmap->y <= radius)
	{
		mmap->x = -radius - 1;
		while (++mmap->x <= radius)
		{
			if (mmap->x * mmap->x + mmap->y * mmap->y <= radius * radius)
			{
				mmap->map_x = mmap->player_x + mmap->x;
				mmap->map_y = mmap->player_y + mmap->y;
				if (mmap->map_x >= 0 && mmap->map_x < img->width
					&& mmap->map_y >= 0 && mmap->map_y < img->height)
				{
					dst = img->addr + (mmap->map_y * img->line_len + mmap->map_x
							* (img->bpp / 8));
					*(unsigned int *)dst = 0x00FF2222;
				}
			}
		}
	}
}

void	setup_minimap(t_minimap *mmap, t_config *cfg)
{
	mmap->scale = get_minimap_scale(&cfg->win, &cfg->map);
	mmap->origin_x = MINIMAP_MARGIN;
	mmap->origin_y = cfg->win.height - (cfg->map.height * mmap->scale)
		- MINIMAP_MARGIN;
	mmap->player_x = mmap->origin_x + (int)(cfg->player.pos_x * mmap->scale);
	mmap->player_y = mmap->origin_y + (int)(cfg->player.pos_y * mmap->scale);
	mmap->map_y = 0;
}

void	render_minimap_tiles(t_minimap *mmap, t_config *cfg)
{
	while (mmap->map_y < cfg->map.height)
	{
		mmap->map_x = 0;
		while (mmap->map_x < cfg->map.width)
		{
			if (mmap->map_x < (int)ft_strlen(cfg->map.map[mmap->map_y]))
				mmap->cell = cfg->map.map[mmap->map_y][mmap->map_x];
			else
				mmap->cell = ' ';
			if (mmap->cell == '1')
				mmap->color = COLOR_DARK_BROWN;
			else if (mmap->cell == '0' || ft_strchr("NESW", mmap->cell))
				mmap->color = COLOR_BEIGE_CLAIR;
			else
				mmap->color = COLOR_TETE_BRULEE;
			minimap_draw_square(&cfg->win, mmap->origin_x + mmap->map_x
				* mmap->scale, mmap->origin_y + mmap->map_y * mmap->scale,
				mmap->color);
			mmap->map_x++;
		}
		mmap->map_y++;
	}
}

void	draw_minimap(t_config *cfg)
{
	t_minimap	mmap;

	setup_minimap(&mmap, cfg);
	render_minimap_tiles(&mmap, cfg);
	draw_minimap_player(&cfg->win, &mmap, 3);
	draw_minimap_rays(cfg, mmap.origin_x, mmap.origin_y, mmap.scale);
}
