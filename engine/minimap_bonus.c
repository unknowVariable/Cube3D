/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alix <alix@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 05:15:00 by aconstan          #+#    #+#             */
/*   Updated: 2025/05/23 10:31:08 by alix             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static int	minimap_get_color(char c)
{
	if (c == '1')
		return (WALL_COLOR);
	if (c == '0')
		return (FLOOR_COLOR);
	return (VOID_COLOR);
}

static void	minimap_draw_square(t_minimap *ctx, int px, int py, int color)
{
	int		i;
	int		j;
	char	*dst;

	i = 0;
	while (i < ctx->scale)
	{
		j = 0;
		while (j < ctx->scale)
		{
			if (px + i >= 0 && px + i < ctx->img->width && py + j >= 0 && py
				+ j < ctx->img->height)
			{
				dst = ctx->img->addr + ((py + j) * ctx->img->line_len + (px + i)
						* (ctx->img->bpp / 8));
				*(unsigned int *)dst = color;
			}
			j++;
		}
		i++;
	}
}

static void	minimap_draw_cells(t_config *cfg, t_minimap *ctx)
{
	int	mx;
	int	my;

	my = 0;
	while (my < cfg->map.height)
	{
		mx = 0;
		while (mx < cfg->map.width)
		{
			minimap_draw_square(ctx, ctx->origin_x + mx * ctx->scale,
				ctx->origin_y + my * ctx->scale,
				minimap_get_color(cfg->map.map[my][mx]));
			mx++;
		}
		my++;
	}
}

static void	minimap_draw_cursor(t_config *cfg, t_minimap *ctx)
{
	int	px;
	int	py;
	int	i;
	int	j;

	px = ctx->origin_x + (int)(cfg->player.pos_x * ctx->scale);
	py = ctx->origin_y + (int)(cfg->player.pos_y * ctx->scale);
	i = -3;
	while (i <= 3)
	{
		j = -3;
		while (j <= 3)
		{
			minimap_draw_square(ctx, px + i, py + j, CURSOR_COLOR);
			j++;
		}
		i++;
	}
}

void	draw_minimap(t_config *cfg)
{
	t_minimap	ctx;
	int			scale_x;
	int			scale_y;
	int			mh;

	ctx.img = &cfg->win;
	scale_x = (cfg->win.width / 4) / cfg->map.width;
	scale_y = (cfg->win.height / 4) / cfg->map.height;
	ctx.scale = scale_x;
	if (scale_y < scale_x)
		ctx.scale = scale_y;
	if (ctx.scale < 3)
		ctx.scale = 3;
	mh = cfg->map.height * ctx.scale;
	ctx.origin_x = MINIMAP_MARGIN;
	ctx.origin_y = ctx.img->height - mh - MINIMAP_MARGIN;
	minimap_draw_cells(cfg, &ctx);
	minimap_draw_cursor(cfg, &ctx);
}
