/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 14:17:25 by hitran            #+#    #+#             */
/*   Updated: 2024/08/20 00:35:19 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	validate_path(t_map *map, char *map_path)
{
	int		len;

	map->fd = open(map_path, O_RDONLY);
	if (map->fd < 0)
		handle_file_error(map, map_path, strerror(errno));
	len = ft_strlen(map_path);
	while (ft_is_white_space(map_path[--len]))
		;
	if (map_path[len -3] == '.' && map_path[len -2] == 'b'
		&& map_path[len -1] == 'e' && map_path[len] == 'r')
		len -= 3;
	else
		handle_file_error(map, map_path, "Not a .ber file");
	while (len > 0 && map_path[len] != '/')
		len--;
	if (map_path[len] == '/')
		len++;
	if (map_path[len] == '.')
		handle_file_error(map, map_path, "Hidden file");
}

static void	flood_fill(t_map *map, char **visited, int x, int y)
{
	if (visited[x][y] == '1')
		return ;
	if (visited[x][y] == 'C')
		map->c_paths++;
	else if (visited[x][y] == 'E')
		map->e_paths = 1;
	visited[x][y] = '1';
	flood_fill(map, visited, x + 1, y);
	flood_fill(map, visited, x - 1, y);
	flood_fill(map, visited, x, y + 1);
	flood_fill(map, visited, x, y - 1);
}

static void	validate_objects(t_map *map)
{
	char	**visited;

	if (map->c_count < 1)
		handle_map_error(map, "Collectible not found");
	if (map->p_count < 1)
		handle_map_error(map, "Player not found");
	if (map->p_count > 1)
		handle_map_error(map, "More than 1 player");
	if (map->e_count < 1)
		handle_map_error(map, "Exit not found");
	if (map->e_count > 1)
		handle_map_error(map, "More than 1 exit");
	visited = ft_matrix_dup(map->arr, map->rows);
	if (!visited)
		handle_map_error(map, "More than 1 exit");
	flood_fill(map, visited, map->p_row, map->p_col);
	ft_free_triptr(&visited);
	if (!map->e_paths)
		handle_map_error(map, "No valid path to exit");
	if (map->c_paths != map->c_count)
		handle_map_error(map, "No valid path to all collectibles");
}

void	validate_map(t_map *map, int row, int col)
{
	while (++row < map->rows)
	{
		if ((int)(ft_strlen(map->arr[row])) != map->cols)
			handle_map_error(map, "Not rectangular");
		col = -1;
		while (++col < map->cols)
		{
			if (!ft_strchr("01CEPX\n", map->arr[row][col]))
				handle_map_error(map, "Invalid characters");
			if (map->arr[row][0] != '1' || map->arr[row][map->cols -1] != '1'
				|| map->arr[0][col] != '1' || map->arr[map->rows -1][col] != 49)
				handle_map_error(map, "Not enclosed by walls");
			if (map->arr[row][col] == 'P')
			{
				map->p_count++;
				map->p_row = row;
				map->p_col = col;
			}
			if (map->arr[row][col] == 'C')
				map->c_count++;
			if (map->arr[row][col] == 'E')
				map->e_count++;
		}
	}
	validate_objects(map);
}

void	read_map(t_map *map, char *map_path)
{
	int		byte;
	char	line[BUFFER_SIZE];

	validate_path(map, map_path);
	ft_bzero(line, BUFFER_SIZE);
	byte = read(map->fd, line, BUFFER_SIZE);
	if (byte == -1)
		handle_map_error(map, "Reading failed");
	else if (byte == 0)
		handle_map_error(map, "Empty map");
	else if (byte > MAX_COL * (MAX_ROW + 1))
		handle_map_error(map, "Is too large");
	map->arr = ft_split(line, '\n');
	if (!map->arr)
		handle_map_error(map, "Split failed");
	map->cols = ft_strlen(map->arr[0]);
	map->rows = ft_matrixlen(map->arr);
	if (ft_count_char(line, '\n') > map->rows - 1)
		handle_map_error(map, "Empty lines");
	if (map->cols > MAX_COL || map->rows > MAX_ROW)
		handle_map_error(map, "Exceeds the maximum size");
	validate_map(map, -1, -1);
}
