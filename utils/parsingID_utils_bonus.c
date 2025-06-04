/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsingID_utils_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alix <alix@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 05:15:00 by aconstan          #+#    #+#             */
/*   Updated: 2025/06/04 19:37:54 by alix             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cube3d_bonus.h"

int	is_identifier(char *line)
{
	return (ft_strncmp(line, "NO", 2) == 0 || ft_strncmp(line, "SO", 2) == 0
		|| ft_strncmp(line, "WE", 2) == 0 || ft_strncmp(line, "EA", 2) == 0);
}

int	all_identifiers_filled(t_config *conf)
{
	return (conf->no_path && conf->so_path && conf->we_path && conf->ea_path);
}

static void	exit_bad_field(t_config *c, char *v, char *msg)
{
	free(v);
	clean_exit(c, msg);
}

void	set_config_field(t_config *c, char *id, char *line)
{
	char	*v;

	v = ft_strtrim(line, " \t\n");
	if (!v)
		clean_exit(c, "Erreur allocation mémoire");
	if ((!ft_strcmp(id, "F") || !ft_strcmp(id, "C")) && !is_valid_rgb(v))
		exit_bad_field(c, v, "Couleur invalide");
	if (!ft_strcmp(id, "NO") && !c->no_path)
		c->no_path = ft_strdup(v);
	else if (!ft_strcmp(id, "SO") && !c->so_path)
		c->so_path = ft_strdup(v);
	else if (!ft_strcmp(id, "WE") && !c->we_path)
		c->we_path = ft_strdup(v);
	else if (!ft_strcmp(id, "EA") && !c->ea_path)
		c->ea_path = ft_strdup(v);
	else
		exit_bad_field(c, v, "Identifiant invalide ou déjà défini");
	printf("Stocké [%s] = [%s]\n", id, v);
	free(v);
}
