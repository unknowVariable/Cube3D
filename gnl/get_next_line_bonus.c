/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alix <alix@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 05:15:00 by aconstan          #+#    #+#             */
/*   Updated: 2025/06/02 15:34:12 by alix             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cube3d.h"

char	*ft_join_free(char *str1, char *str2)
{
	char	*temp;

	temp = ft_strjoin(str1, str2);
	free(str1);
	return (temp);
}

static char	*extract_first_line(char *buffer)
{
	int		i;
	char	*line;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	line = ft_calloc(i + 2, sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

static void	remove_first_line(char *buffer)
{
	char	*nl;
	int		i;

	nl = ft_strchr(buffer, '\n');
	i = 0;
	if (!nl)
	{
		buffer[0] = '\0';
		return ;
	}
	nl++;
	while (nl[i])
	{
		buffer[i] = nl[i];
		i++;
	}
	buffer[i] = '\0';
}

static int	fill_buffer(int fd, char *buffer)
{
	char	stash[BUFFER_SIZE + 1];
	char	*temp;
	int		r;

	temp = ft_calloc(1, 1);
	r = 1;
	if (!temp)
		return (0);
	while (!ft_strchr(temp, '\n') && r > 0)
	{
		r = read(fd, stash, BUFFER_SIZE);
		if (r == -1)
			return (free(temp), 0);
		stash[r] = '\0';
		temp = ft_join_free(temp, stash);
	}
	ft_strncpy(buffer, temp, BUFFER_SIZE);
	free(temp);
	return (1);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1] = {0};
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!ft_strchr(buffer, '\n') && buffer[0] == '\0')
		if (!fill_buffer(fd, buffer))
			return (NULL);
	line = extract_first_line(buffer);
	if (!line && buffer[0] != '\0')
	{
		line = ft_strdup(buffer);
		buffer[0] = '\0';
		return (line);
	}
	remove_first_line(buffer);
	return (line);
}
