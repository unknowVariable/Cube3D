#include "cube3d.h"

int	can_move_x(t_config *conf, int nx)
{
	int		map_y = (int)conf->player.pos_y;
	
	if (map_y >= 0 && map_y < conf->map.height && (int)nx >= 0 && (int)nx < (int)ft_strlen(conf->map.map[map_y]))
		return (1);
	return (0);
}

int	can_move_y(t_config *conf, int ny)
{
	int		map_x = (int)conf->player.pos_x;
	
	if ((int)ny >= 0 && (int)ny < conf->map.height &&
		map_x >= 0 && map_x < (int)ft_strlen(conf->map.map[(int)ny]))
		return (1);
	return (0);
}
