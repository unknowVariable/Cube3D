#include "cube3d.h"

void render_scene(t_config *conf)
{
    conf->win.img = mlx_new_image(conf->mlx.mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
    conf->win.addr = mlx_get_data_addr(conf->win.img, &conf->win.bpp, &conf->win.line_len, &conf->win.endian);
    for (int x = 0; x < WIN_WIDTH; x++)
    {
        double cameraX = 2 * x / (double)WIN_WIDTH - 1;
        double rayDirX = conf->player.dir_x + conf->player.plane_x * cameraX;
        double rayDirY = conf->player.dir_y + conf->player.plane_y * cameraX;
        int side;
        double perp = perform_dda(conf, rayDirX, rayDirY, &side);
        int lineHeight = (int)(WIN_HEIGHT / perp);
        int drawStart = -lineHeight / 2 + WIN_HEIGHT / 2;
        if (drawStart < 0) drawStart = 0;
        int drawEnd = lineHeight / 2 + WIN_HEIGHT / 2;
        if (drawEnd >= WIN_HEIGHT) drawEnd = WIN_HEIGHT - 1;
        double wallX = (side == 0) ? conf->player.pos_y + perp * rayDirY : conf->player.pos_x + perp * rayDirX;
        wallX -= floor(wallX);
        int texX = (int)(wallX * (double)TEX_WIDTH);

        // NOUVEAU : Choix dynamique de la texture
        t_img_data	tex_img;
        if (side == 0 && rayDirX > 0)
            tex_img = conf->mlx.tex_ea;
        else if (side == 0 && rayDirX < 0)
            tex_img = conf->mlx.tex_we;
        else if (side == 1 && rayDirY > 0)
            tex_img = conf->mlx.tex_so;
        else
            tex_img = conf->mlx.tex_no;

        tex_img.addr = mlx_get_data_addr(tex_img.img, &tex_img.bpp, &tex_img.line_len, &tex_img.endian);

        draw_column(conf, tex_img, x, drawStart, drawEnd, texX, lineHeight);
    }
    mlx_put_image_to_window(conf->mlx.mlx_ptr, conf->mlx.win_ptr, conf->win.img, 0, 0);
    mlx_destroy_image(conf->mlx.mlx_ptr, conf->win.img);
}

