/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_move_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alix <alix@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 05:15:00 by aconstan          #+#    #+#             */
/*   Updated: 2025/05/25 01:14:35 by alix             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	mouse_move(int x, int y, void *param)
{
	static int  last_x;
	double  rot;
	t_config *conf;
	(void)y;
    
    *conf = param;
    last_x = -1;
	if (last_x == -1)
		last_x = x;
	rot = (x - last_x) * MOUSESENSITIVITY;
	if (rot != 0)
		rotate_view(conf, rot);
	last_x = x;
	return (0);
}
