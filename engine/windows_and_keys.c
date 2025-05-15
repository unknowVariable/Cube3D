#include "cube3d.h"

int	close_window(void *param)
{
	t_config *c = (t_config *)param;

	free_mlx_resources(c);
	free_paths_and_colors(c);
	if (c->map.raw_lines)
		free_list(c->map.raw_lines);
	if (c->map.map)
		free_map(c->map.map);
	exit(0); 
}

int	handle_key(int keycode, void *param)
{
	if (keycode == KEY_ESC || keycode == 65307)
		close_window(param);
	return (0);
}
