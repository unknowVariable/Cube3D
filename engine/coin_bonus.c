/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coin_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alix <alix@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 05:15:00 by aconstan          #+#    #+#             */
/*   Updated: 2025/05/24 05:12:11 by alix             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	load_coin_anim(t_config *cfg)
{
	int	i;

	char *filenames[COIN_ANIM_FRAMES] = {
		"./textures/coin_0.xpm",
		"./textures/coin_1.xpm",
		"./textures/coin_2.xpm",
		"./textures/coin_3.xpm",
		"./textures/coin_4.xpm",
		"./textures/coin_5.xpm",
	};
	i = 0;
	while (i < COIN_ANIM_FRAMES)
	{
		cfg->coin.img[i] = mlx_xpm_file_to_image(cfg->mlx.mlx_ptr, filenames[i],
				&cfg->coin.width, &cfg->coin.height);
		if (!cfg->coin.img[i])
			ft_exit_error("Erreur chargement image pièce animée");
		i++;
	}
	cfg->coin.frame = 0;
}

void	draw_coin_anim(t_config *cfg)
{
	static int	frame_count = 0;
	int			x;
	int			y;

	x = cfg->win.width - cfg->coin.width - 10;
	y = 10;
	mlx_put_image_to_window(cfg->mlx.mlx_ptr, cfg->mlx.win_ptr,
		cfg->coin.img[cfg->coin.frame], x, y);
	frame_count++;
	if (frame_count > COIN_ANIM_SPEED)
	{
		cfg->coin.frame = (cfg->coin.frame + 1) % COIN_ANIM_FRAMES;
		frame_count = 0;
	}
}
