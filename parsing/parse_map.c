/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alix <alix@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 05:15:00 by aconstan          #+#    #+#             */
/*   Updated: 2025/06/05 23:00:15 by alix             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cube3d_bonus.h"

void	handle_player_error(t_config *cfg, char *line, char *msg)
{
	free(line);
	clean_exit(cfg, msg);
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

void	validate_map_line(t_map_data *map, t_config *cfg, char *line, int y)
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
				handle_player_error(cfg, line, "Multiple players");
			xy[0] = x;
			process_player(map, line[x], xy);
		}
		else if (!is_map_char(line[x]))
			handle_player_error(cfg, line, "Invalid map char");
		x++;
	}
}

void	store_map_line(t_map_data *map, t_config *cfg, char *line)
{
	char	*trimmed;

	trimmed = ft_strtrim(line, "\n");
	if (!trimmed)
		clean_and_exit(cfg, line, NULL, "Malloc error");
	create_padded_line(map, trimmed);
	free(trimmed);
	map->height++;
}

void	parse_map_lines(t_map_data *map, t_config *config, int fd, char *line)
{
	int	y;

	y = 0;
	while (line)
	{
		if (is_only_spaces(line))
		{
			free(line);
			clean_exit(config, "Ligne vide dans la carte");
		}
		store_map_line(map, config, line);
		validate_map_line(map, config, line, y++);
		free(line);
		line = get_next_line(fd);
	}
	if (!map->player_found)
		clean_exit(config, "Aucun joueur trouvé dans la carte");
	map->map = list_to_tab(map->raw_lines, map->height, config);
	if (!map->map)
		clean_exit(config, "Erreur lors de la transformation de la carte");
	check_map_closed(map->map, map->height, map->width, config);
}
