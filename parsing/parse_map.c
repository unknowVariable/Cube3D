#include "../header/cube3d.h"

void	process_player_position(t_map_data *map, t_config *config, char c, int x, int y, char *line)
{
	if (map->player_found)
	{
		free(line);
		clean_exit(config, "Plus d’un joueur trouvé");
	}
	map->player_found = 1;
	map->player_x = x;
	map->player_y = y;
	map->player_dir = c;
}

void	validate_map_line(t_map_data *map, t_config *config, char *line, int y)
{
	int	x = 0;

	while (line[x] && line[x] != '\n')
	{
		if (is_player_char(line[x]))
		{
			if (map->player_found)
			{
				free(line);
				clean_exit(config, "Plus d’un joueur trouvé");
			}
			process_player_position(map, config, line[x], x, y, line);
		}
		else if (!is_map_char(line[x]))
		{
			free(line);
			clean_exit(config,"Caractère invalide dans la carte");
		}
		x++;
	}
}

void	store_map_line(t_map_data *map, t_config *config, char *line)
{
	char	*padded;
	char	*trimmed;
	int		len;

	trimmed = ft_strtrim(line, "\n");
	if (!trimmed)
	{
		free(line);
		clean_exit(config, "Erreur malloc strtrim");
	}
	len = ft_strlen(trimmed);
	if (len > map->width)
		map->width = len;

	padded = malloc(map->width + 1);
	if (!padded)
	{
		free(trimmed);
		free(line);
		clean_exit(config, "Erreur malloc ligne map");
	}

	ft_memcpy(padded, trimmed, len);
	if (len < map->width)
		ft_memset(padded + len, ' ', map->width - len);
	padded[map->width] = '\0';

	ft_lstadd_back(&map->raw_lines, ft_lstnew(ft_strdup(padded)));
	free(padded);
	free(trimmed);
	map->height++;
}

void parse_map_lines(t_map_data *map, t_config *config, int fd, char *line)
{
    int y = 0;

    while (line)
    {
        if (is_only_spaces(line))
        {
            free(line);
            clean_exit(config,"Ligne vide dans la carte");
        }
        store_map_line(map, config, line);
        validate_map_line(map, config, line, y++);
        free(line);
        line = get_next_line(fd);
    }
    if (!map->player_found)
        clean_exit(config,"Aucun joueur trouvé dans la carte");

    map->map = list_to_tab(map->raw_lines, map->height, config);
    if (!map->map)
        clean_exit(config, "Erreur lors de la transformation de la carte");

    check_map_closed(map->map, map->height, map->width, config);
}

