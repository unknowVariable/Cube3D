/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsingMAP_utils2_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alix <alix@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 05:15:00 by aconstan          #+#    #+#             */
/*   Updated: 2025/06/05 23:38:21 by alix             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cube3d_bonus.h"


char	**list_to_tab(t_list *lst, int height, int width, t_config *config)
{
	char	**tab;
	int		i, j;
	char	*line;
	int		len;

	tab = malloc(sizeof(char *) * (height + 1));
	if (!tab)
		return (NULL);
	i = 0;
	while (lst)
	{
		line = (char *)lst->content;
		len = ft_strlen(line);
		tab[i] = malloc(width + 1);
		if (!tab[i])
			return (NULL);
		for (j = 0; j < width; j++)
		{
			if (j < len)
				tab[i][j] = line[j];
			else
				tab[i][j] = '0'; // ou ' ', selon la logique souhaitée
		}
		tab[i][width] = '\0';
		// Ici, tu peux faire ta détection des 'C'
		for (j = 0; j < width; j++)
		{
			if (tab[i][j] == 'C')
			{
				add_map_coin(&config->map, j, i);
				tab[i][j] = '0';
			}
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
