/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   windows_and_keys.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alix <alix@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 05:15:00 by aconstan          #+#    #+#             */
/*   Updated: 2025/05/23 00:21:44 by alix             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	close_window(void *param)
{
	t_config	*c;

	c = (t_config *)param;
	free_mlx_resources(c);
	free_paths_and_colors(c);
	if (c->map.raw_lines)
		free_list(c->map.raw_lines);
	if (c->map.map)
		free_map(c->map.map);
	exit(0);
}

int	key_press(int key, void *param)
{
	t_config	*conf;

	conf = (t_config *)param;
	conf->keys[key] = 1;
	if (key == KEY_ESC)
		close_window(param);
	return (0);
}

int	key_release(int key, void *param)
{
	t_config	*conf;

	printf("KEY PRESSED");
	conf = (t_config *)param;
	conf->keys[key] = 0;
	return (0);
}

void	handle_jump(t_config *conf)
{
	printf("Jumping? %d offset=%.2f speed=%.2f\n", conf->jumping, conf->jump_offset, conf->jump_speed);
	if (conf->keys[32] && conf->jumping == 0 && conf->jump_offset == 0)
	{
		conf->jumping = 1;
		conf->jump_speed = 6.0;
	}
	if (conf->jumping)
	{
		conf->jump_offset += conf->jump_speed;
		conf->jump_speed -= 0.5;
		if (conf->jump_offset <= 0)
		{
			conf->jump_offset = 0;
			conf->jumping = 0;
			conf->jump_speed = 0;
		}
	}
}

int	game_loop(void *param)
{
	t_config	*conf;

	conf = (t_config *)param;
	conf->move_speed = 0.010;
	conf->rot_speed = 0.010;
	if (conf->keys[KEY_ESC])
		close_window(conf);
	if (conf->keys[KEY_W])
		move_forward(conf, conf->move_speed);
	if (conf->keys[KEY_S])
		move_backward(conf, conf->move_speed);
	if (conf->keys[KEY_A])
		strafe_left(conf, conf->move_speed);
	if (conf->keys[KEY_D])
		strafe_right(conf, conf->move_speed);
	if (conf->keys[KEY_LEFT])
		rotate_view(conf, -conf->rot_speed);
	if (conf->keys[KEY_RIGHT])
		rotate_view(conf, conf->rot_speed);
	handle_jump(conf);
	render_scene(conf);
	return (0);
}
