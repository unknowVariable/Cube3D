/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_content.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alix <alix@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 05:15:00 by aconstan          #+#    #+#             */
/*   Updated: 2025/05/22 10:24:23 by alix             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cube3d.h"

void	parse_identifier_line(t_config *conf, char *line)
{
	while (*line == ' ' || *line == '\t')
		line++;
	if (ft_strncmp(line, "NO", 2) == 0)
		set_config_field(conf, "NO", line + 2);
	else if (ft_strncmp(line, "SO", 2) == 0)
		set_config_field(conf, "SO", line + 2);
	else if (ft_strncmp(line, "WE", 2) == 0)
		set_config_field(conf, "WE", line + 2);
	else if (ft_strncmp(line, "EA", 2) == 0)
		set_config_field(conf, "EA", line + 2);
	else if (ft_strncmp(line, "F", 1) == 0)
		set_config_field(conf, "F", line + 1);
	else if (ft_strncmp(line, "C", 1) == 0)
		set_config_field(conf, "C", line + 1);
	else
		clean_exit(conf, "Identifiant invalide");
}

static char	*skip_empty_lines_after_ids(t_config *config, int fd, char *line)
{
	while (line && is_only_spaces(line))
	{
		free(line);
		line = get_next_line(fd);
	}
	if (!line)
		clean_exit(config, "Carte manquante");
	return (line);
}

static char	*process_line(t_config *conf, char *line)
{
	if (is_only_spaces(line))
	{
		free(line);
		return (NULL);
	}
	if (is_identifier(line))
		parse_identifier_line(conf, line);
	else if (!all_identifiers_filled(conf))
	{
		free(line);
		clean_exit(conf, "Invalid pre-map line");
	}
	return (line);
}

void	parse_file(int fd, t_config *conf)
{
	char	*line;
	int		processing;

	processing = 1;
	line = get_next_line(fd);
	while (line != NULL && processing)
	{
		line = process_line(conf, line);
		if (line && !is_identifier(line) && all_identifiers_filled(conf))
			processing = 0;
		else
		{
			free(line);
			line = get_next_line(fd);
		}
	}
	if (!line)
		clean_exit(conf, "Missing map");
	if (!all_identifiers_filled(conf))
		clean_exit(conf, "Missing identifiers");
	line = skip_empty_lines_after_ids(conf, fd, line);
	parse_map_lines(&conf->map, conf, fd, line);
}
