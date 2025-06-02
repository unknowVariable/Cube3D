/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alix <alix@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 05:15:00 by aconstan          #+#    #+#             */
/*   Updated: 2025/06/02 16:49:50 by alix             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d_bonus.h"

int	get_tex_color_at(t_img_data *tex, double fx, double fy)
{
	int		tex_x;
	int		tex_y;

	tex_x = (int)(fx * tex->width) % tex->width;
	tex_y = (int)(fy * tex->height) % tex->height;
	if (tex_x < 0)
		tex_x += tex->width;
	if (tex_y < 0)
		tex_y += tex->height;
	return (((int *)tex->addr)[tex->width * tex_y + tex_x]);
}

int	get_ceil_tex_color(t_img_data *tex, double fx, double fy)
{
	int		tex_x;
	int		tex_y;

	tex_x = (int)(fx * tex->width) % tex->width;
	tex_y = tex->height - 1 - ((int)(fy * tex->height) % tex->height);
	if (tex_x < 0)
		tex_x += tex->width;
	if (tex_y < 0)
		tex_y += tex->height;
	return (((int *)tex->addr)[tex->width * tex_y + tex_x]);
}
void	draw_column(t_config *conf, t_img_data tex_img)
{
	double	step;
	int		color;
	int		y;
	double	current_dist;
	double	weight;
	double	floor_wall_x;
	double	floor_wall_y;
	double	fx;
	double	fy;
	int		ceil_y;

	y = 0;
	step = 1.0 * tex_img.height / conf->ray.line_height;
	tex_img.tex_pos = (conf->ray.draw_start - (double)WIN_HEIGHT / 2
			+ (double)conf->ray.line_height / 2) * step;

	if (conf->ray.side == 0 && conf->ray.ray_dir_x > 0)
	{
		floor_wall_x = conf->ray.map_x;
		floor_wall_y = conf->ray.map_y + conf->ray.wall_x;
	}
	else if (conf->ray.side == 0 && conf->ray.ray_dir_x < 0)
	{
		floor_wall_x = conf->ray.map_x + 1.0;
		floor_wall_y = conf->ray.map_y + conf->ray.wall_x;
	}
	else if (conf->ray.side == 1 && conf->ray.ray_dir_y > 0)
	{
		floor_wall_x = conf->ray.map_x + conf->ray.wall_x;
		floor_wall_y = conf->ray.map_y;
	}
	else
	{
		floor_wall_x = conf->ray.map_x + conf->ray.wall_x;
		floor_wall_y = conf->ray.map_y + 1.0;
	}

	while (y < conf->ray.draw_start)
	{
		ceil_y = WIN_HEIGHT - y - 1;
		current_dist = (double)WIN_HEIGHT / (2.0 * ceil_y - WIN_HEIGHT);
		weight = current_dist / conf->ray.perp_wall_dist;
		fx = weight * floor_wall_x + (1.0 - weight) * conf->player.pos_x;
		fy = weight * floor_wall_y + (1.0 - weight) * conf->player.pos_y;
		color = get_tex_color_at(&conf->ceil_tex, fx, fy);
		put_pixel(conf, y, color);
		y++;
	}
	while (y <= conf->ray.draw_end)
	{
		tex_img.y = (int)tex_img.tex_pos & (tex_img.height - 1);
		tex_img.tex_pos += step;
		color = *(unsigned int *)(tex_img.addr + tex_img.y * tex_img.line_len
				+ tex_img.x * (tex_img.bpp / 8));
		put_pixel(conf, y, color);
		y++;
	}
	while (y < WIN_HEIGHT)
	{
		current_dist = (double)WIN_HEIGHT / (2.0 * y - WIN_HEIGHT);
		weight = current_dist / conf->ray.perp_wall_dist;
		fx = weight * floor_wall_x + (1.0 - weight) * conf->player.pos_x;
		fy = weight * floor_wall_y + (1.0 - weight) * conf->player.pos_y;
		color = get_tex_color_at(&conf->floor_tex, fx, fy);
		put_pixel(conf, y, color);
		y++;
	}
}


static void	init_ray_dir_and_delta(t_config *conf, t_ray *ray)
{  
	ray->camera_x = 2 * conf->win.x / (double)WIN_WIDTH - 1;
	ray->ray_dir_x = conf->player.dir_x + conf->player.plane_x * ray->camera_x;
	ray->ray_dir_y = conf->player.dir_y + conf->player.plane_y * ray->camera_x;
	ray->map_x = (int)conf->player.pos_x;
	ray->map_y = (int)conf->player.pos_y;
	if (ray->ray_dir_x == 0)
		ray->delta_x = 1e30;
	else
		ray->delta_x = my_abs(1 / ray->ray_dir_x);
	if (ray->ray_dir_y == 0)
		ray->delta_y = 1e30;
	else
		ray->delta_y = my_abs(1 / ray->ray_dir_y);
}

void	cast_ray(t_config *conf, t_ray *ray)
{
	init_ray_dir_and_delta(conf, ray);
	ray->perp_wall_dist = perform_dda(conf, ray);
	ray->line_height = (int)(WIN_HEIGHT / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + WIN_HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + WIN_HEIGHT / 2;
	if (ray->draw_end >= WIN_HEIGHT)
		ray->draw_end = WIN_HEIGHT - 1;
	if (ray->side == 0)
		ray->wall_x = conf->player.pos_y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		ray->wall_x = conf->player.pos_x + ray->perp_wall_dist * ray->ray_dir_x;
	ray->wall_x -= floor(ray->wall_x);
}

t_img_data	get_good_tex(t_config *conf)
{
	t_img_data	tex_img;

	if (conf->ray.side == 0 && conf->ray.ray_dir_x > 0)
		tex_img = conf->mlx.tex_ea;
	else if (conf->ray.side == 0 && conf->ray.ray_dir_x < 0)
		tex_img = conf->mlx.tex_we;
	else if (conf->ray.side == 1 && conf->ray.ray_dir_y > 0)
		tex_img = conf->mlx.tex_so;
	else
		tex_img = conf->mlx.tex_no;
	return (tex_img);
}

void	render_scene(t_config *conf)
{
	t_img_data	tex_img;

	conf->win.img = mlx_new_image(conf->mlx.mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	conf->win.addr = mlx_get_data_addr(conf->win.img, &conf->win.bpp,
			&conf->win.line_len, &conf->win.endian);
	conf->win.width = WIN_WIDTH;
	conf->win.height = WIN_HEIGHT;
	conf->win.x = 0;
	while (conf->win.x < WIN_WIDTH)
	{
		cast_ray(conf, &conf->ray);
		tex_img = get_good_tex(conf);
		tex_img.x = (int)(conf->ray.wall_x * (double)TEX_WIDTH);
		tex_img.addr = mlx_get_data_addr(tex_img.img, &tex_img.bpp,
				&tex_img.line_len, &tex_img.endian);
		draw_column(conf, tex_img);
		conf->win.x++;
	}
	mlx_put_image_to_window(conf->mlx.mlx_ptr, conf->mlx.win_ptr, conf->win.img,
		0, 0);
	mlx_destroy_image(conf->mlx.mlx_ptr, conf->win.img);
}
