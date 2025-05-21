#include "cube3d.h"

void	put_pixel(char *data, int x, int y, int color, int bpp, int line_len)
{
	int	offset = y * line_len + x * (bpp / 8);
	*(unsigned int *)(data + offset) = color;
}

