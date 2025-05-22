/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsingMAP_utils3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alix <alix@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 05:15:00 by aconstan          #+#    #+#             */
/*   Updated: 2025/05/22 21:44:54 by alix             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cube3d.h"

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
