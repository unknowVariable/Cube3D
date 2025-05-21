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

int key_press(int key, void *param)
{
    t_config *conf = (t_config *)param;
    conf->keys[key] = 1;
    if (key == KEY_ESC)
        close_window(param);
    return (0);
}

int key_release(int key, void *param)
{
    t_config *conf = (t_config *)param;
    conf->keys[key] = 0;
    return (0);
}

int game_loop(void *param)
{
    t_config *conf = (t_config *)param;
    double movespeed = 0.010;
    double rotspeed = 0.010;

    // Quitter aussi si ESC reste appuyé
    if (conf->keys[KEY_ESC])
        close_window(conf);

    if (conf->keys[KEY_W])
        move_forward(conf, movespeed);
    if (conf->keys[KEY_S])
        move_backward(conf, movespeed);
    if (conf->keys[KEY_A])
        strafe_left(conf, movespeed);
    if (conf->keys[KEY_D])
        strafe_right(conf, movespeed);
    if (conf->keys[KEY_LEFT])
        rotate_view(conf, -rotspeed);
    if (conf->keys[KEY_RIGHT])
        rotate_view(conf, rotspeed);
    render_scene(conf);
    return (0);
}
