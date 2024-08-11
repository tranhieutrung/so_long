/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 14:17:25 by hitran            #+#    #+#             */
/*   Updated: 2024/08/11 20:05:00 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	validate_path(t_map *map, char *map_path)
{
	int		len;

	map->fd = open(map_path, O_RDONLY);
	if (map->fd < 0)
	{
		perror("Error: Map");
		exit (1);
	}
	len = ft_strlen(map_path);
	while (ft_is_white_space(map_path[--len]))
		;
	if (map_path[len -3] == '.' && map_path[len -2] == 'b'
		&& map_path[len -1] == 'e' && map_path[len] == 'r')
		len -= 3;
	else
		handle_map_error(map, NULL, "Error: Map: Not a .ber file");
	while (len > 0 && map_path[len] != '/')
		len--;
	if (map_path[len] == '/')
		len++;
	if (map_path[len] == '.')
		handle_map_error(map, NULL, "Error: Map: Hidden file");
}

static char	*read_line(t_map *map, int column)
{
	int		byte;
	char	c;
	char	*line;

	line = (char *)ft_calloc(MAX_COL + 1, sizeof(char));
	if (!line)
		handle_map_error(map, NULL, "Error: Map: Memory allocation failed");
	while (1)
	{
		if (column > MAX_COL - 1)
			handle_map_error(map, line, "Error: Map: Exceeds the maximum size");
		byte = read(map->fd, &c, 1);
		if (byte == -1)
			handle_map_error(map, NULL, "Error: Map: Reading failed");
		else if (byte == 0 && column == 0)
			return (ft_free_return(line));
		else if (!ft_strchr("01CEPX\n", c))
			handle_map_error(map, line, "Error: Map: Invalid characters");
		else if (byte == 0 || c == '\n')
			break ;
		line[column++] = c;
	}
	return (line);
}

void	read_map(t_map *map, char *map_path)
{
	validate_path(map, map_path);
	map->arr = (char **)ft_calloc(MAX_ROW + 1, sizeof(char *));
	while (1)
	{
		map->arr[map->row] = read_line(map, 0);
		if (map->arr[map->row] && !ft_strlen(map->arr[map->row]))
			handle_map_error(map, NULL, "Error: Map: Empty lines");
		if (map->arr[map->row] == NULL)
			break  ;
		map->row++;
		if (map->row > MAX_ROW)
			handle_map_error(map, NULL, "Error: Map: Exceeds the maximum size");
	}
	if (!map->row)
		handle_map_error(map, NULL, "Error: Map: Empty map");
	map->col = ft_strlen(map->arr[0]);
	validate_map(map, -1, -1);
}
