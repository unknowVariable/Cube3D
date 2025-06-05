/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alix <alix@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 05:15:00 by aconstan          #+#    #+#             */
/*   Updated: 2025/06/05 23:17:07 by alix             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d_bonus.h"

int	get_tex_coord(int size, double f)
{
	int	coord;

	coord = (int)(f * size) % size;
	if (coord < 0)
		coord += size;
	return (coord);
}

static void	init_ray_dir_and_delta(t_config *conf, t_ray *ray)
{
	ray->camera_x = 2 * conf->win.x / (double)WIN_WIDTH - 1;
	ray->ray_dir_x = conf->player.dir_x + conf->player.plane_x * ray->camera_x;
	ray->ray_dir_y = conf->player.dir_y + conf->player.plane_y * ray->camera_x;
	ray->map_x = (int)conf->player.pos_x;
	ray->map_y = (int)conf->player.pos_y;
	if (ray->ray_dir_x == 0)
		ray->delta_x = 1e30;
	else
		ray->delta_x = my_abs(1 / ray->ray_dir_x);
	if (ray->ray_dir_y == 0)
		ray->delta_y = 1e30;
	else
		ray->delta_y = my_abs(1 / ray->ray_dir_y);
}

void	cast_ray(t_config *conf, t_ray *ray)
{
	init_ray_dir_and_delta(conf, ray);
	ray->perp_wall_dist = perform_dda(conf, ray);
	ray->line_height = (int)(WIN_HEIGHT / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + WIN_HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + WIN_HEIGHT / 2;
	if (ray->draw_end >= WIN_HEIGHT)
		ray->draw_end = WIN_HEIGHT - 1;
	if (ray->side == 0)
		ray->wall_x = conf->player.pos_y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		ray->wall_x = conf->player.pos_x + ray->perp_wall_dist * ray->ray_dir_x;
	ray->wall_x -= floor(ray->wall_x);
}

t_img_data	get_good_tex(t_config *conf)
{
	t_img_data	tex_img;

	if (conf->ray.side == 0 && conf->ray.ray_dir_x > 0)
		tex_img = conf->mlx.tex_ea;
	else if (conf->ray.side == 0 && conf->ray.ray_dir_x < 0)
		tex_img = conf->mlx.tex_we;
	else if (conf->ray.side == 1 && conf->ray.ray_dir_y > 0)
		tex_img = conf->mlx.tex_so;
	else
		tex_img = conf->mlx.tex_no;
	return (tex_img);
}

void render_scene(t_config *conf)
{
    t_img_data  tex_img;

    // Vérifications initiales complètes
    if (!conf || !conf->mlx.mlx_ptr || !conf->mlx.win_ptr)
    {
        printf("Error: MLX not initialized\n");
        return;
    }

    // Création de l'image avec vérification
    conf->win.img = mlx_new_image(conf->mlx.mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
    if (!conf->win.img)
    {
        printf("Error: Failed to create new image\n");
        return;
    }

    // Récupération des données de l'image
    conf->win.addr = mlx_get_data_addr(conf->win.img, &conf->win.bpp,
                    &conf->win.line_len, &conf->win.endian);
    if (!conf->win.addr)
    {
        mlx_destroy_image(conf->mlx.mlx_ptr, conf->win.img);
        printf("Error: Failed to get image address\n");
        return;
    }

    // Initialisation des propriétés de la fenêtre
    conf->win.width = WIN_WIDTH;
    conf->win.height = WIN_HEIGHT;
    conf->win.x = 0;

    // Rendu colonne par colonne
    while (conf->win.x < WIN_WIDTH)
    {
        // Lancement du raycasting
        cast_ray(conf, &conf->ray);

        // Récupération de la texture appropriée avec vérification
        tex_img = get_good_tex(conf);
        if (!tex_img.img)
        {
            conf->win.x++;
            continue;
        }

        // Calcul de la position de la texture
        tex_img.x = (int)(conf->ray.wall_x * (double)TEX_WIDTH);
        if (tex_img.x < 0 || tex_img.x >= TEX_WIDTH)
            tex_img.x = 0;

        // Récupération des données de la texture
        tex_img.addr = mlx_get_data_addr(tex_img.img, &tex_img.bpp,
                        &tex_img.line_len, &tex_img.endian);
        if (!tex_img.addr)
        {
            conf->win.x++;
            continue;
        }

        // Rendu de la colonne
        draw_column(conf, tex_img);
        conf->win.x++;
    }

    // Affichage de l'image finale
    mlx_put_image_to_window(conf->mlx.mlx_ptr, conf->mlx.win_ptr, conf->win.img, 0, 0);

    // Nettoyage
    mlx_destroy_image(conf->mlx.mlx_ptr, conf->win.img);
    conf->win.img = NULL;
    conf->win.addr = NULL;
}
