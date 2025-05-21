#include "cube3d.h"

double my_abs(double x)
{
	return (x < 0) ? -x : x;
}

double perform_dda(t_config *conf, double ray_dir_x, double ray_dir_y, int *side)
{
	int map_x = (int)conf->player.pos_x;
	int map_y = (int)conf->player.pos_y;
	double delta_x = (ray_dir_x == 0) ? 1e30 : my_abs(1 / ray_dir_x);
	double delta_y = (ray_dir_y == 0) ? 1e30 : my_abs(1 / ray_dir_y);
	double side_x, side_y;
	int step_x, step_y;

	if (ray_dir_x < 0)
	{
		step_x = -1;
		side_x = (conf->player.pos_x - map_x) * delta_x;
	}
	else
	{
		step_x = 1;
		side_x = (map_x + 1.0 - conf->player.pos_x) * delta_x;
	}
	if (ray_dir_y < 0)
	{
		step_y = -1;
		side_y = (conf->player.pos_y - map_y) * delta_y;
	}
	else
	{
		step_y = 1;
		side_y = (map_y + 1.0 - conf->player.pos_y) * delta_y;
	}
	while (conf->map.map[map_y][map_x] != '1')
	{
		if (side_x < side_y)
		{
			side_x += delta_x;
			map_x += step_x;
			*side = 0;
		}
		else
		{
			side_y += delta_y;
			map_y += step_y;
			*side = 1;
		}
	}
	return (*side == 0) ? side_x - delta_x : side_y - delta_y;
}
