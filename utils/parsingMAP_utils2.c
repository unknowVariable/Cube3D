/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsingMAP_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alix <alix@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 05:15:00 by aconstan          #+#    #+#             */
/*   Updated: 2025/05/22 22:41:30 by alix             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cube3d.h"

char	**list_to_tab(t_list *lst, int height, t_config *config)
{
	char	**tab;
	int		i;

	(void)config;
	i = 0;
	tab = malloc(sizeof(char *) * (height + 1));
	if (!tab)
		return (NULL);
	while (lst)
	{
		tab[i] = ft_strdup(lst->content);
		if (!tab[i])
		{
			while (i--)
				free(tab[i]);
			free(tab);
			return (NULL);
		}
		i++;
		lst = lst->next;
	}
	tab[i] = NULL;
	return (tab);
}

int	is_void(char c)
{
	return (c == ' ');
}

int	is_floor_or_player(char c)
{
	return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

void	check_map_closed(char **map, int height, int width, t_config *c)
{
	int	i;
	int	j;

	(void)width;
	i = 0;
	while (i < height)
	{
		j = 0;
		while (map[i][j])
		{
			if (is_floor_or_player(map[i][j]))
			{
				if (i == 0 || j == 0 || i == height - 1
					|| j >= (int)ft_strlen(map[i]) - 1)
					clean_exit(c, "Carte ouverte (bord)");
				if (i + 1 >= height || j + 1 >= (int)ft_strlen(map[i + 1]) || j
					- 1 < 0 || i - 1 < 0 || j >= (int)ft_strlen(map[i - 1])
					|| is_void(map[i + 1][j]) || is_void(map[i - 1][j])
					|| is_void(map[i][j + 1]) || is_void(map[i][j - 1]))
					clean_exit(c, "Carte ouverte (adjacent espace)");
			}
			j++;
		}
		i++;
	}
}
