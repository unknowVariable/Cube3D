/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alix <alix@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 05:15:00 by aconstan          #+#    #+#             */
/*   Updated: 2025/05/22 08:09:01 by alix             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cube3d_bonus.h"

void	ft_exit_error(char *msg)
{
	int	i;

	i = 0;
	write(2, "Error\n", 6);
	while (msg[i])
	{
		write(2, &msg[i], 1);
		i++;
	}
	exit(EXIT_FAILURE);
}

void	free_list(t_list *lst)
{
	t_list	*tmp;

	while (lst)
	{
		tmp = lst->next;
		free(lst->content);
		free(lst);
		lst = tmp;
	}
}

void	free_paths_and_colors(t_config *c)
{
	if (c->no_path)
		free(c->no_path);
	if (c->so_path)
		free(c->so_path);
	if (c->we_path)
		free(c->we_path);
	if (c->ea_path)
		free(c->ea_path);
}

void	free_mlx_resources(t_config *c)
{
	free_floor_and_ceiling(c);
	free_coin_images(c);
	if (c->mlx.tex_no.img)
		mlx_destroy_image(c->mlx.mlx_ptr, c->mlx.tex_no.img);
	if (c->mlx.tex_so.img)
		mlx_destroy_image(c->mlx.mlx_ptr, c->mlx.tex_so.img);
	if (c->mlx.tex_we.img)
		mlx_destroy_image(c->mlx.mlx_ptr, c->mlx.tex_we.img);
	if (c->mlx.tex_ea.img)
		mlx_destroy_image(c->mlx.mlx_ptr, c->mlx.tex_ea.img);
	if (c->mlx.win_ptr)
		mlx_destroy_window(c->mlx.mlx_ptr, c->mlx.win_ptr);
	if (c->mlx.mlx_ptr)
	{
		mlx_destroy_display(c->mlx.mlx_ptr);
		free(c->mlx.mlx_ptr);
	}
}

void	clean_exit(t_config *c, char *msg)
{
	free_mlx_resources(c);
	free_paths_and_colors(c);
	if (c->map.raw_lines)
		free_list(c->map.raw_lines);
	if (c->map.map)
		free_map(c->map.map);
	ft_exit_error(msg);
}
