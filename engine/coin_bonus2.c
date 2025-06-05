/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coin_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alix <alix@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 05:15:00 by aconstan          #+#    #+#             */
/*   Updated: 2025/05/24 05:54:06 by alix             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d_bonus.h"

int	should_draw_coin_pixel(int color)
{
	if (color == 0xFF00FF)
		return (0);
	return (1);
}

void	set_coin_filenames(char **filenames)
{
	filenames[0] = "./textures/coin_0.xpm";
	filenames[1] = "./textures/coin_1.xpm";
	filenames[2] = "./textures/coin_2.xpm";
	filenames[3] = "./textures/coin_3.xpm";
	filenames[4] = "./textures/coin_4.xpm";
	filenames[5] = "./textures/coin_5.xpm";
}

void	load_coin_anim(t_config *cfg)
{
	int		i;
	char	*filenames[COIN_ANIM_FRAMES];

	set_coin_filenames(filenames);
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
