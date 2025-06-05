/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alix <alix@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 05:15:00 by aconstan          #+#    #+#             */
/*   Updated: 2025/06/05 23:56:35 by alix             ###   ########.fr       */
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
	t_list	*lines;
	int		height;
	int		width;
	int		len;

	lines = NULL;
	height = 0;
	width = 0;
	while (line)
	{
		len = ft_strlen(line);
		if (len > 0 && !is_only_spaces(line)) // IGNORE les lignes vides ou blanches !
		{
			if (len > width)
				width = len;
			ft_lstadd_back(&lines, ft_lstnew(ft_strdup(line)));
			height++;
		}
		free(line);
		line = get_next_line(fd);
	}
	map->raw_lines = lines;
	map->height = height;
	map->width = width;

	map->map = list_to_tab(map->raw_lines, map->height, map->width, config);
	if (!map->map)
		clean_exit(config, "Erreur lors de la transformation de la carte");
}

// bpmis change 