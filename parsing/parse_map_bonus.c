/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alix <alix@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 05:15:00 by aconstan          #+#    #+#             */
/*   Updated: 2025/06/03 19:36:42 by alix             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cube3d_bonus.h"

static void	init_doors(t_config *conf, char **map)
{
	int	y;
	int	x;
	int	i;

	y = -1;
	conf->door_count = 0;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
			if (map[y][x] == 'D')
				conf->door_count++;
	}
	if (!(conf->doors = malloc(sizeof(t_door) * conf->door_count)))
		clean_exit(conf, "Doors malloc failed");
	y = -1;
	i = 0;
	while (map[++y] && i < conf->door_count)
	{
		x = -1;
		while (map[y][++x])
			if (map[y][x] == 'D')
				conf->doors[i++] = (t_door){x, y, 0};
	}
}

void	validate_map_line(t_map_data *map, t_config *conf, char *line, int y)
{
	int	x;
	int	xy[2];

	x = 0;
	xy[1] = y;
	while (line[x] && line[x] != '\n')
	{
		if (is_player_char(line[x]))
		{
			if (map->player_found)
				handle_player_error(conf, line, "Multiple players");
			xy[0] = x;
			process_player(map, line[x], xy);
		}
		else if (!is_map_char(line[x]) && line[x] != 'D')
			handle_player_error(conf, line, "Invalid map character");
		x++;
	}
}

void		parse_map_lines(t_map_data *map, t_config *conf, int fd, char *line)
{
	int	y;

	y = 0;
	while (line)
	{
		if (is_only_spaces(line))
			clean_and_exit(conf, line, NULL, "Empty line in map");
		store_map_line(map, conf, line);
		validate_map_line(map, conf, line, y++);
		free(line);
		line = get_next_line(fd);
	}
	if (!map->player_found)
		clean_exit(conf, "No player found");
	map->map = list_to_tab(map->raw_lines, map->height, conf);
	check_map_closed(map->map, map->height, map->width, conf);
	init_doors(conf, map->map);
}