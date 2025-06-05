/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alix <alix@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 05:15:00 by aconstan          #+#    #+#             */
/*   Updated: 2025/06/02 18:18:04 by alix             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d_bonus.h"

int	mouse_move(int x, int y, void *param)
{
	static int	last_x;
	double		rot;
	t_config	*conf;

	conf = param;
	(void)y;
	if (last_x == 0)
		last_x = x;
	rot = (x - last_x) * MOUSESENSITIVITY;
	if (rot != 0)
		rotate_view(conf, rot);
	last_x = x;
	return (0);
}
