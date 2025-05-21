#include "cube3d.h"

void	draw_column( char *data, char *tex_data, int x,
	int draw_start, int draw_end, int tex_x, int line_height,
	int bpp, int line_len, int tex_bpp, int tex_line_len,
	int tex_height, int win_height, int ceil_color, int floor_color)
{

	double	step = 1.0 * tex_height / line_height;
	double	tex_pos = (draw_start - win_height / 2 + line_height / 2) * step;
	int		y = 0;

	while (y < draw_start)
		put_pixel(data, x, y++, ceil_color, bpp, line_len);
	while (y <= draw_end)
	{
		int tex_y = (int)tex_pos & (tex_height - 1);
		tex_pos += step;
		int color = *(unsigned int *)(tex_data + tex_y * tex_line_len + tex_x * (tex_bpp / 8));
		put_pixel(data, x, y++, color, bpp, line_len);
	}
	while (y < win_height)
		put_pixel(data, x, y++, floor_color, bpp, line_len);
}