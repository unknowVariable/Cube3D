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

void	draw_coin_pixel(t_config *cfg, int x, int y, t_coin_draw *ctx)
{
	int	color;

	color = *(unsigned int *)(ctx->src_addr + y * ctx->size_line + x * (ctx->bpp
				/ 8));
	if (should_draw_coin_pixel(color))
		mlx_pixel_put(cfg->mlx.mlx_ptr, cfg->mlx.win_ptr, ctx->pos_x + x,
			ctx->pos_y + y, color);
}

void	put_coin_line(t_config *cfg, int y, t_coin_draw *ctx)
{
	int	x;

	x = 0;
	while (x < cfg->coin.width)
	{
		draw_coin_pixel(cfg, x, y, ctx);
		x++;
	}
}

void	put_coin_with_transparency(t_config *cfg, int frame, int pos_x,
		int pos_y)
{
	t_coin_draw	ctx;
	int			endian;
	int			y;

	ctx.src_addr = mlx_get_data_addr(cfg->coin.img[frame], &ctx.bpp,
			&ctx.size_line, &endian);
	ctx.pos_x = pos_x;
	ctx.pos_y = pos_y;
	y = 0;
	while (y < cfg->coin.height)
	{
		put_coin_line(cfg, y, &ctx);
		y++;
	}
}

void	draw_coin_anim(t_config *cfg)
{
	static int	frame_count;
	int			x;
	int			y;

	x = cfg->win.width - cfg->coin.width - 35;
	y = 10;
	put_coin_with_transparency(cfg, cfg->coin.frame, x, y);
	frame_count++;
	if (frame_count > COIN_ANIM_SPEED)
	{
		cfg->coin.frame = (cfg->coin.frame + 1) % COIN_ANIM_FRAMES;
		frame_count = 0;
	}
}

void	display_coins(void *mlx, void *win, int coins)
{
	char	buffer[32];
	int		x;
	int		y;
	int		char_width;

	y = 110;
	char_width = 8;
	sprintf(buffer, "coins : %d", coins);
	x = WIN_WIDTH - (ft_strlen(buffer) * char_width) - 40;
	mlx_string_put(mlx, win, x, y, 0xFF0000, buffer);
}
