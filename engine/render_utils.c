/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alix <alix@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 05:15:00 by aconstan          #+#    #+#             */
/*   Updated: 2025/05/22 22:16:04 by alix             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	put_pixel(t_config *conf, int y, int color)
{
	int		x;
	char	*dst;

	x = conf->win.x;
	if (x < 0 || x >= conf->win.width || y < 0 || y >= conf->win.height)
		return;
	dst = conf->win.addr + (y * conf->win.line_len + x * (conf->win.bpp / 8));
	*(unsigned int *)dst = color;
}
