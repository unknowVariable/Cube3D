#include "cube3d.h"

void	draw_column(t_config *conf, t_img_data tex_img)
{
	double	step;
	int		color;
	int		y;

	y = 0;
	step = 1.0 * tex_img.height / conf->ray.line_height;
	tex_img.tex_pos = (conf->ray.draw_start - (double)WIN_HEIGHT / 2
			+ (double)conf->ray.line_height / 2) * step;
	while (y < conf->ray.draw_start)
		put_pixel(conf, y++, conf->c_color);
	while (y <= conf->ray.draw_end)
	{
		tex_img.y = (int)tex_img.tex_pos & (tex_img.height - 1);
		tex_img.tex_pos += step;
		color = *(unsigned int *)(tex_img.addr + tex_img.y * tex_img.line_len
				+ tex_img.x * (tex_img.bpp / 8));
		put_pixel(conf, y++, color);
	}
	while (y < WIN_HEIGHT)
		put_pixel(conf, y++, conf->f_color);
}
