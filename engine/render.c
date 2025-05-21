#include "cube3d.h"

void	draw_column(t_config *conf, t_img_data tex_img, int x,
	int draw_start, int draw_end, int tex_x, int line_height)
{

	double	step = 1.0 * tex_img.height / line_height;
	double	tex_pos = (draw_start - (double)WIN_HEIGHT / 2 + (double)line_height / 2) * step;
	int		y = 0;

	while (y < draw_start)
		put_pixel(conf->win.addr, x, y++, conf->c_color, conf->win.bpp, conf->win.line_len);
	while (y <= draw_end)
	{
		int tex_y = (int)tex_pos & (tex_img.height - 1);
		tex_pos += step;
		int color = *(unsigned int *)(tex_img.addr + tex_y * tex_img.line_len + tex_x * (tex_img.bpp / 8));
		put_pixel(conf->win.addr, x, y++, color, conf->win.bpp, conf->win.line_len);
	}
	while (y < WIN_HEIGHT)
		put_pixel(conf->win.addr, x, y++, conf->f_color, conf->win.bpp, conf->win.line_len);
}
