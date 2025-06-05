/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alix <alix@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 05:15:00 by aconstan          #+#    #+#             */
/*   Updated: 2025/05/26 07:52:09 by alix             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/cube3d_bonus.h"

int	main(int argc, char **argv)
{
	t_config	conf;
	int			fd;

	if (argc != 2 || !check_extension(argv[1]))
		ft_exit_error("Usage: ./cub3D <fichier.cub>");
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		ft_exit_error("Impossible d'ouvrir le fichier");
	ft_bzero(&conf, sizeof(t_config));
	parse_file(fd, &conf);
	close(fd);
	init_mlx(&conf);
	init_player(&conf);
	mlx_hook(conf.mlx.win_ptr, 17, 0, close_window, &conf);
	mlx_hook(conf.mlx.win_ptr, 2, 1L << 0, key_press, &conf);
	mlx_hook(conf.mlx.win_ptr, 3, 1L << 1, key_release, &conf);
    mlx_hook(conf.mlx.win_ptr, 6, (1L<<6), mouse_move, &conf);
	mlx_loop_hook(conf.mlx.mlx_ptr, game_loop, &conf);
	mlx_loop(conf.mlx.mlx_ptr);
	return (0);
}