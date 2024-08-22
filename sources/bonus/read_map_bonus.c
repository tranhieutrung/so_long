/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 14:17:25 by hitran            #+#    #+#             */
/*   Updated: 2024/08/22 14:08:48 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	flood_fill(t_map *map, char **visited, int32_t row, int32_t col)
{
	if (visited[row][col] == '1' || visited[row][col] == 'T')
		return ;
	if (visited[row][col] == 'C')
		map->c_paths++;
	else if (visited[row][col] == 'E')
		map->e_paths = 1;
	visited[row][col] = '1';
	flood_fill(map, visited, row + 1, col);
	flood_fill(map, visited, row - 1, col);
	flood_fill(map, visited, row, col + 1);
	flood_fill(map, visited, row, col - 1);
}

static void	validate_paths_to_objects(t_map *map)
{
	char	**visited;

	visited = ft_matrix_dup(map->arr, map->rows);
	if (!visited)
		map_error(map, "Memory allocation failed");
	flood_fill(map, visited, map->start.row, map->start.col);
	ft_free_triptr(&visited);
	if (!map->e_paths)
		map_error(map, "No valid path to exit");
	if (map->c_paths != map->c_count)
		map_error(map, "No valid path to all collectibles");
}

static void	validate_objects(t_map *map)
{
	if (map->c_count < 1)
		map_error(map, "Collectible not found");
	if (map->p_count < 1)
		map_error(map, "Player not found");
	if (map->p_count > 1)
		map_error(map, "More than 1 player");
	if (map->e_count < 1)
		map_error(map, "Exit not found");
	if (map->e_count > 1)
		map_error(map, "More than 1 exit");
	validate_paths_to_objects(map);
}

static void	validate_map(t_map *map, int32_t row, int32_t col)
{
	if (map->cols > MAX_COL || map->rows > MAX_ROW)
		map_error(map, "Exceeds the maximum size");
	while (++row < map->rows)
	{
		if ((int32_t)(ft_strlen(map->arr[row])) != map->cols)
			map_error(map, "Is not rectangular");
		col = -1;
		while (++col < map->cols)
		{
			if (!ft_strchr("01CEPT\n", map->arr[row][col]))
				map_error(map, "Contains invalid characters");
			if ((row == 0 || row == map->rows -1 || col == 0
					|| col == map->cols -1) && map->arr[row][col] != '1')
				map_error(map, "Is not surrounded by walls");
			count_objects(map, row, col);
		}
	}
	validate_objects(map);
}

void	read_map(t_map *map, int32_t fd)
{
	int32_t	byte;
	char	line[BUFFER_SIZE];

	ft_bzero(line, BUFFER_SIZE);
	byte = read(fd, line, BUFFER_SIZE);
	close (fd);
	if (byte == -1)
		map_error(NULL, "Reading failed");
	else if (byte == 0)
		map_error(NULL, "Is empty");
	else if (byte > MAX_ROW * (MAX_COL + 1))
		map_error(NULL, "Is too large");
	map->arr = ft_split(line, '\n');
	if (!map->arr)
		map_error(NULL, "Splitting failed");
	map->cols = ft_strlen(map->arr[0]);
	map->rows = ft_matrixlen(map->arr);
	if (ft_count_char(line, '\n') > map->rows - 1)
		map_error(map, "Contains empty lines");
	validate_map(map, -1, -1);
}
