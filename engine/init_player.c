#include "cube3d.h"

void	init_player(t_config *c)
{
	c->player.pos_x = c->map.player_x + 0.5;
	c->player.pos_y = c->map.player_y + 0.5;

	if (c->map.player_dir == 'N')
	{
		c->player.dir_x = 0;
		c->player.dir_y = -1;
		c->player.plane_x = 0.66;
		c->player.plane_y = 0;
	}
	else if (c->map.player_dir == 'S')
	{
		c->player.dir_x = 0;
		c->player.dir_y = 1;
		c->player.plane_x = -0.66;
		c->player.plane_y = 0;
	}
	else if (c->map.player_dir == 'E')
	{
		c->player.dir_x = 1;
		c->player.dir_y = 0;
		c->player.plane_x = 0;
		c->player.plane_y = 0.66;
	}
	else if (c->map.player_dir == 'W')
	{
		c->player.dir_x = -1;
		c->player.dir_y = 0;
		c->player.plane_x = 0;
		c->player.plane_y = -0.66;
	}
}

