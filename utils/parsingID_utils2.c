#include "../header/cube3d.h"

int is_number(char *s)
{
	int i = 0;
	if (!s || !s[0])
		return (0);
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	is_valid_rgb_component(char *s)
{
	char *trimmed;
	int value;

	trimmed = ft_strtrim(s, " \t\n");
	if (!trimmed)
		return (0);
	if (!is_number(trimmed))
	{
		free(trimmed);
		return (0);
	}
	value = ft_atoi(trimmed);
	free(trimmed);
	return (value >= 0 && value <= 255);
}

int	is_valid_rgb(char *str)
{
	char	**split;
	int		i;

	split = ft_split(str, ',');
	if (!split || !split[0] || !split[1] || !split[2] || split[3])
	{
		ft_free_split(split);
		return (0);
	}
	i = 0;
	while (i < 3)
	{
		if (!is_valid_rgb_component(split[i]))
		{
			ft_free_split(split);
			return (0);
		}
		i++;
	}
	ft_free_split(split);
	return (1);
}


int	parse_color_string_to_int(char *str, t_config *c)
{
	char **components;
	int r, g, b;
	int color;

	if (!str)
		clean_exit(c, "Couleur NULL");
	components = ft_split(str, ',');
	if (!components || !components[0] || !components[1] || !components[2] || components[3])
		clean_exit(c, "Format couleur invalide");
	r = ft_atoi(components[0]);
	g = ft_atoi(components[1]);
	b = ft_atoi(components[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		clean_exit(c, "Valeurs RGB hors plage");
	color = (r << 16) | (g << 8) | b;
	ft_free_split(components);
	return (color);
}

