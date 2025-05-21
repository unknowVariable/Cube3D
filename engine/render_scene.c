#include "cube3d.h"

void render_scene(t_config *conf)
{
    int w = 1024, h = 768;
    void *img = mlx_new_image(conf->mlx.mlx_ptr, w, h);
    int bpp, line_len, endian;
    char *data = mlx_get_data_addr(img, &bpp, &line_len, &endian);
    int tex_w = 128, tex_h = 128;
    int tex_bpp, tex_line_len, tex_endian;
    int ceil_color = parse_color_string_to_int(conf->c_color, conf);
    int floor_color = parse_color_string_to_int(conf->f_color, conf);

    for (int x = 0; x < w; x++)
    {
        double cameraX = 2 * x / (double)w - 1;
        double rayDirX = conf->player.dir_x + conf->player.plane_x * cameraX;
        double rayDirY = conf->player.dir_y + conf->player.plane_y * cameraX;
        int side;
        double perp = perform_dda(conf, rayDirX, rayDirY, &side);
        int lineHeight = (int)(h / perp);
        int drawStart = -lineHeight / 2 + h / 2;
        if (drawStart < 0) drawStart = 0;
        int drawEnd = lineHeight / 2 + h / 2;
        if (drawEnd >= h) drawEnd = h - 1;
        double wallX = (side == 0) ? conf->player.pos_y + perp * rayDirY : conf->player.pos_x + perp * rayDirX;
        wallX -= floor(wallX);
        int texX = (int)(wallX * (double)tex_w);

        // NOUVEAU : Choix dynamique de la texture
        void *tex_img;
        if (side == 0 && rayDirX > 0)
            tex_img = conf->mlx.tex_ea;
        else if (side == 0 && rayDirX < 0)
            tex_img = conf->mlx.tex_we;
        else if (side == 1 && rayDirY > 0)
            tex_img = conf->mlx.tex_so;
        else
            tex_img = conf->mlx.tex_no;

        char *tex_data = mlx_get_data_addr(tex_img, &tex_bpp, &tex_line_len, &tex_endian);

        draw_column(data, tex_data, x, drawStart, drawEnd, texX, lineHeight,
            bpp, line_len, tex_bpp, tex_line_len, tex_h, h, ceil_color, floor_color);
    }
    mlx_put_image_to_window(conf->mlx.mlx_ptr, conf->mlx.win_ptr, img, 0, 0);
    mlx_destroy_image(conf->mlx.mlx_ptr, img);
}

