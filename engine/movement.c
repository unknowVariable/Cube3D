/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alix <alix@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 05:15:00 by aconstan          #+#    #+#             */
/*   Updated: 2025/05/25 11:34:59 by alix             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	move_forward(t_config *conf, double speed)
{
	double	nx;
	double	ny;

	nx = conf->player.pos_x + conf->player.dir_x * speed;
	ny = conf->player.pos_y + conf->player.dir_y * speed;
	if (conf->map.map[(int)conf->player.pos_y][(int)nx] != '1')
		conf->player.pos_x = nx;
	if (conf->map.map[(int)ny][(int)conf->player.pos_x] != '1')
		conf->player.pos_y = ny;
}

void	move_backward(t_config *conf, double speed)
{
	double	nx;
	double	ny;

	nx = conf->player.pos_x - conf->player.dir_x * speed;
	ny = conf->player.pos_y - conf->player.dir_y * speed;
	if (conf->map.map[(int)conf->player.pos_y][(int)nx] != '1')
		conf->player.pos_x = nx;
	if (conf->map.map[(int)ny][(int)conf->player.pos_x] != '1')
		conf->player.pos_y = ny;
}

void	strafe_left(t_config *conf, double speed)
{
	double	nx;
	double	ny;

	nx = conf->player.pos_x - (conf->player.plane_x) * speed;
	ny = conf->player.pos_y - conf->player.plane_y * speed;
	if (conf->map.map[(int)conf->player.pos_y][(int)nx] != '1')
		conf->player.pos_x = nx;
	if (conf->map.map[(int)ny][(int)conf->player.pos_x] != '1')
		conf->player.pos_y = ny;
}

void	strafe_right(t_config *conf, double speed)
{
	double	nx;
	double	ny;

	nx = conf->player.pos_x + (conf->player.plane_x) * speed;
	ny = conf->player.pos_y + (conf->player.plane_y) * speed;
	if (conf->map.map[(int)conf->player.pos_y][(int)nx] != '1')
		conf->player.pos_x = nx;
	if (conf->map.map[(int)ny][(int)conf->player.pos_x] != '1')
		conf->player.pos_y = ny;
}

void	rotate_view(t_config *conf, double rot)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = conf->player.dir_x;
	old_plane_x = conf->player.plane_x;
	conf->player.dir_x = conf->player.dir_x * cos(rot) - conf->player.dir_y
		* sin(rot);
	conf->player.dir_y = old_dir_x * sin(rot) + conf->player.dir_y * cos(rot);
	conf->player.plane_x = conf->player.plane_x * cos(rot)
		- conf->player.plane_y * sin(rot);
	conf->player.plane_y = old_plane_x * sin(rot) + conf->player.plane_y
		* cos(rot);
}
