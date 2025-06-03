/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsingMAP_utils3_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alix <alix@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 05:15:00 by aconstan          #+#    #+#             */
/*   Updated: 2025/06/03 19:36:10 by alix             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cube3d_bonus.h"

void	clean_and_exit(t_config *cfg, char *s1, char *s2, char *msg)
{
	free(s1);
	free(s2);
	clean_exit(cfg, msg);
}

void	create_padded_line(t_map_data *map, char *trimmed)
{
	char	*padded;
	int		len;

	len = ft_strlen(trimmed);
	if (len > map->width)
		map->width = len;
	padded = malloc(map->width + 1);
	if (!padded)
		return ;
	ft_memcpy(padded, trimmed, len);
	if (len < map->width)
		ft_memset(padded + len, ' ', map->width - len);
	padded[map->width] = '\0';
	ft_lstadd_back(&map->raw_lines, ft_lstnew(padded));
}

void	handle_player_error(t_config *conf, char *line, char *msg)
{
	free(line);
	clean_exit(conf, msg);
}

void	process_player(t_map_data *map, char c, int xy[2])
{
	if (map->player_found)
		return ;
	map->player_found = 1;
	map->player_x = xy[0];
	map->player_y = xy[1];
	map->player_dir = c;
}

void	store_map_line(t_map_data *map, t_config *conf, char *line)
{
	char	*trimmed;

	trimmed = ft_strtrim(line, "\n");
	if (!trimmed)
		clean_and_exit(conf, line, NULL, "Malloc failed");
	create_padded_line(map, trimmed);
	free(trimmed);
	map->height++;
}
