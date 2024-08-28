/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 14:17:25 by hitran            #+#    #+#             */
/*   Updated: 2024/08/28 10:32:28 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	file_error(int32_t fd, char *path, char *message)
{
	if (fd > 2)
		close(fd);
	ft_printf_fd(2, "Error\n%s: %s\n", path, message);
	exit (EXIT_FAILURE);
}

static int32_t	validate_path(char *path)
{
	int32_t		len;
	int32_t		fd;

	if (!path[0] || ft_is_all_white_spaces(path))
		file_error(0, path, "Is an empty path");
	fd = open(path, O_RDONLY);
	if (fd < 0)
		file_error(0, path, strerror(errno));
	len = ft_strlen(path);
	if (path[len - 4] != '.' || path[len - 3] != 'b'
		|| path[len - 2] != 'e' || path[len - 1] != 'r')
		file_error(fd, path, "Not a .ber file");
	return (fd);
}

int	main(int argc, char **argv)
{
	t_solong	sl;
	t_map		map;
	int32_t		fd;

	if (argc != 2)
	{
		ft_printf_fd(2, "Error\nUsage: ./so_long [map_path]/[map_name].ber");
		return (1);
	}
	ft_bzero(&map, sizeof(map));
	fd = validate_path(argv[1]);
	read_map(&map, fd);
	ft_bzero(&sl, sizeof(sl));
	sl.map = &map;
	start_solong(&sl);
	exit_solong(&sl, EXIT_SUCCESS);
}
