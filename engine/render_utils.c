#include "cube3d.h"

void	put_pixel(t_config *conf, int y, int color)
{
	int	offset = y * conf->win.line_len + conf->win.x * (conf->win.bpp / 8);
	*(unsigned int *)(conf->win.addr + offset) = color;
}

