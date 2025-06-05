/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alix <alix@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 05:15:00 by aconstan          #+#    #+#             */
/*   Updated: 2025/05/22 08:09:01 by alix             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cube3d_bonus.h"

void	free_floor_and_ceiling(t_config *c)
{
	if (c->floor_tex.img)
		mlx_destroy_image(c->mlx.mlx_ptr, c->floor_tex.img);
	if (c->ceil_tex.img)
		mlx_destroy_image(c->mlx.mlx_ptr, c->ceil_tex.img);
}

void	free_coin_images(t_config *c)
{
	int	i;

	i = 0;
	while (i < COIN_ANIM_FRAMES)
	{
		if (c->coin.img[i])
			mlx_destroy_image(c->mlx.mlx_ptr, c->coin.img[i]);
		i++;
	}
}
