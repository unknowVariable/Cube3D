#include "../header/cube3d.h"

// Verify the .cub extension on file
int	check_extension(char *filename)
{
	int len = ft_strlen(filename);
	if (len < 5 || ft_strcmp(filename + len - 4, ".cub") != 0)
		ft_exit_error("File should be : name.cub");
	return (1);
}

// Verify if the file can be open
int	open_file(char *filename)
{
	int fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		ft_exit_error("File can't be open");
	return (fd);
}

int	check_and_open_file(char *filename)
{
	int fd;

	check_extension(filename);
	fd = open_file(filename);
	return (fd);
}
