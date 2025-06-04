/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene_bonus2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alix <alix@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 05:15:00 by aconstan          #+#    #+#             */
/*   Updated: 2025/06/04 20:52:32 by alix             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d_bonus.h"

int	get_tex_color_at(t_img_data *tex, double fx, double fy)
{
	int	tex_x;
	int	tex_y;
	int	*data;

	tex_x = get_tex_coord(tex->width, fx);
	tex_y = get_tex_coord(tex->height, fy);
	data = (int *)tex->addr;
	return (data[tex->width * tex_y + tex_x]);
}

void	get_floor_wall_xy(t_config *conf, double *wx, double *wy)
{
	if (conf->ray.side == 0 && conf->ray.ray_dir_x > 0)
	{
		*wx = conf->ray.map_x;
		*wy = conf->ray.map_y + conf->ray.wall_x;
	}
	else if (conf->ray.side == 0)
	{
		*wx = conf->ray.map_x + 1.0;
		*wy = conf->ray.map_y + conf->ray.wall_x;
	}
	else if (conf->ray.ray_dir_y > 0)
	{
		*wx = conf->ray.map_x + conf->ray.wall_x;
		*wy = conf->ray.map_y;
	}
	else
	{
		*wx = conf->ray.map_x + conf->ray.wall_x;
		*wy = conf->ray.map_y + 1.0;
	}
}

void draw_ceiling_column(t_config *conf, int end, double wx, double wy)
{
    int y;
    int ceil_y;
    double vals[4];

    y = 0;
    while (y < end)
    {
        ceil_y = WIN_HEIGHT - y - 1;
        vals[0] = (double)WIN_HEIGHT / (2.0 * ceil_y - WIN_HEIGHT);
        vals[1] = vals[0] / conf->ray.perp_wall_dist;
        vals[2] = vals[1] * wx + (1.0 - vals[1]) * conf->player.pos_x;
        vals[3] = vals[1] * wy + (1.0 - vals[1]) * conf->player.pos_y;
        put_pixel(conf, conf->ray.x, y, 
                 get_tex_color_at(&conf->ceil_tex, vals[2], vals[3]));
        y++;
    }
}

void draw_floor_column(t_config *conf, int start, double wx, double wy)
{
    int y;
    double dist;
    double weight;
    double fx;
    double fy;

    y = start;
    while (y < WIN_HEIGHT)
    {
        dist = (double)WIN_HEIGHT / (2.0 * y - WIN_HEIGHT);
        weight = dist / conf->ray.perp_wall_dist;
        fx = weight * wx + (1.0 - weight) * conf->player.pos_x;
        fy = weight * wy + (1.0 - weight) * conf->player.pos_y;
        put_pixel(conf, conf->ray.x, y, 
                 get_tex_color_at(&conf->floor_tex, fx, fy));
        y++;
    }
}

void draw_column(t_config *conf, t_img_data tex_img)
{
    double step;
    double wx;
    double wy;
    int y;
    int color;

    get_floor_wall_xy(conf, &wx, &wy);
    step = 1.0 * tex_img.height / conf->ray.line_height;
    tex_img.tex_pos = (conf->ray.draw_start - (double)WIN_HEIGHT / 2
            + (double)conf->ray.line_height / 2) * step;
    draw_ceiling_column(conf, conf->ray.draw_start, wx, wy);
    y = conf->ray.draw_start;
    while (y <= conf->ray.draw_end)
    {
        tex_img.y = (int)tex_img.tex_pos & (tex_img.height - 1);
        tex_img.tex_pos += step;
        color = *(unsigned int *)(tex_img.addr + tex_img.y * tex_img.line_len
                + tex_img.x * (tex_img.bpp / 8));
        put_pixel(conf, conf->ray.x, y, color);
        y++;
    }
    draw_floor_column(conf, y, wx, wy);
}
