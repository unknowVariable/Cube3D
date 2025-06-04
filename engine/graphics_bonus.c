/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alix <alix@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 05:15:00 by aconstan          #+#    #+#             */
/*   Updated: 2025/06/04 21:08:49 by alix             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d_bonus.h"

#include "cube3d_bonus.h"

static void verify_texture_loading(t_config *conf, t_img_data *tex, const char *name)
{
	(void)name; // Pour éviter l'avertissement de variable inutilisée
    if (!tex->img || !tex->addr || tex->width <= 0 || tex->height <= 0)
    {
        printf("Error: Failed to load texture - ");
        
        clean_exit(conf, "Texture loading failed");
    }
    
    // Vérification d'alignement mémoire pour ARM
    if ((uintptr_t)tex->addr % sizeof(unsigned int) != 0)
    {
        printf("Warning: Unaligned texture memory for - ");
    }
}

void load_floor_and_ceiling_textures(t_config *conf)
{
    conf->floor_tex.img = mlx_xpm_file_to_image(conf->mlx.mlx_ptr,
            "textures/floor.xpm", &conf->floor_tex.width,
            &conf->floor_tex.height);
    if (conf->floor_tex.img)
        conf->floor_tex.addr = mlx_get_data_addr(conf->floor_tex.img,
                &conf->floor_tex.bpp, &conf->floor_tex.line_len,
                &conf->floor_tex.endian);
    
    conf->ceil_tex.img = mlx_xpm_file_to_image(conf->mlx.mlx_ptr,
            "textures/ceil.xpm", &conf->ceil_tex.width, &conf->ceil_tex.height);
    if (conf->ceil_tex.img)
        conf->ceil_tex.addr = mlx_get_data_addr(conf->ceil_tex.img,
                &conf->ceil_tex.bpp, &conf->ceil_tex.line_len,
                &conf->ceil_tex.endian);
    
    verify_texture_loading(conf, &conf->floor_tex, "floor");
    verify_texture_loading(conf, &conf->ceil_tex, "ceiling");
}

void init_door_texture(t_config *conf)
{
    conf->door_tex.img = mlx_xpm_file_to_image(conf->mlx.mlx_ptr,
            "textures/door.xpm",
            &conf->door_tex.width,
            &conf->door_tex.height);
    if (conf->door_tex.img)
        conf->door_tex.addr = mlx_get_data_addr(conf->door_tex.img,
                &conf->door_tex.bpp,
                &conf->door_tex.line_len,
                &conf->door_tex.endian);
    
    verify_texture_loading(conf, &conf->door_tex, "door");
}

void init_mlx_window_buffer(t_config *conf)
{
    conf->win.img = mlx_new_image(conf->mlx.mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
    if (!conf->win.img)
        clean_exit(conf, "Failed to create image buffer");
    
    conf->win.addr = mlx_get_data_addr(conf->win.img,
            &conf->win.bpp, &conf->win.line_len, &conf->win.endian);
    
    // Ajustement de l'alignement pour ARM
    if (conf->win.line_len % sizeof(unsigned int) != 0)
    {
        conf->win.line_len += sizeof(unsigned int) - (conf->win.line_len % sizeof(unsigned int));
        printf("Adjusted line length for memory alignment");
    }
    
    if (!conf->win.addr)
        clean_exit(conf, "Failed to get image buffer address");
}

void init_mlx(t_config *conf)
{
    // Initialisation de la connexion MLX
    conf->mlx.mlx_ptr = mlx_init();
    if (!conf->mlx.mlx_ptr)
        clean_exit(conf, "MLX initialization failed");
    
    // Création de la fenêtre
    conf->mlx.win_ptr = mlx_new_window(conf->mlx.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "Cube3D");
    if (!conf->mlx.win_ptr)
        clean_exit(conf, "Window creation failed");
    
    // Chargement des textures murales
    conf->mlx.tex_no.img = mlx_xpm_file_to_image(conf->mlx.mlx_ptr,
            conf->no_path, &conf->mlx.tex_no.width, &conf->mlx.tex_no.height);
    if (conf->mlx.tex_no.img)
        conf->mlx.tex_no.addr = mlx_get_data_addr(conf->mlx.tex_no.img,
                &conf->mlx.tex_no.bpp, &conf->mlx.tex_no.line_len,
                &conf->mlx.tex_no.endian);
    
    conf->mlx.tex_so.img = mlx_xpm_file_to_image(conf->mlx.mlx_ptr,
            conf->so_path, &conf->mlx.tex_so.width, &conf->mlx.tex_so.height);
    if (conf->mlx.tex_so.img)
        conf->mlx.tex_so.addr = mlx_get_data_addr(conf->mlx.tex_so.img,
                &conf->mlx.tex_so.bpp, &conf->mlx.tex_so.line_len,
                &conf->mlx.tex_so.endian);
    
    conf->mlx.tex_we.img = mlx_xpm_file_to_image(conf->mlx.mlx_ptr,
            conf->we_path, &conf->mlx.tex_we.width, &conf->mlx.tex_we.height);
    if (conf->mlx.tex_we.img)
        conf->mlx.tex_we.addr = mlx_get_data_addr(conf->mlx.tex_we.img,
                &conf->mlx.tex_we.bpp, &conf->mlx.tex_we.line_len,
                &conf->mlx.tex_we.endian);
    
    conf->mlx.tex_ea.img = mlx_xpm_file_to_image(conf->mlx.mlx_ptr,
            conf->ea_path, &conf->mlx.tex_ea.width, &conf->mlx.tex_ea.height);
    if (conf->mlx.tex_ea.img)
        conf->mlx.tex_ea.addr = mlx_get_data_addr(conf->mlx.tex_ea.img,
                &conf->mlx.tex_ea.bpp, &conf->mlx.tex_ea.line_len,
                &conf->mlx.tex_ea.endian);
    
    // Vérification des textures
    verify_texture_loading(conf, &conf->mlx.tex_no, "North");
    verify_texture_loading(conf, &conf->mlx.tex_so, "South");
    verify_texture_loading(conf, &conf->mlx.tex_we, "West");
    verify_texture_loading(conf, &conf->mlx.tex_ea, "East");
    
    // Initialisation du buffer d'image
    init_mlx_window_buffer(conf);
    
    // Chargement des textures supplémentaires
    load_floor_and_ceiling_textures(conf);
    init_door_texture(conf);
    
    // Vérification finale
    if (!conf->win.addr || !conf->win.img)
        clean_exit(conf, "Final window buffer verification failed");
}