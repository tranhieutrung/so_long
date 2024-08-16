/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 08:22:40 by hitran            #+#    #+#             */
/*   Updated: 2024/08/16 15:25:16 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	flood_fill(t_map *map, char **visited, int x, int y)
{
	if (visited[x][y] == '1')
		return ;
	if (visited[x][y] == 'C')
		map->c_path++;
	else if (visited[x][y] == 'E')
		map->e_path = 1;
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
		handle_map_error(map, NULL, "Error: Map: Collectible not found");
	if (map->p_count < 1)
		handle_map_error(map, NULL, "Error: Map: Player not found");
	if (map->p_count > 1)
		handle_map_error(map, NULL, "Error: Map: More than 1 player");
	if (map->e_count < 1)
		handle_map_error(map, NULL, "Error: Map: Exit not found");
	if (map->e_count > 1)
		handle_map_error(map, NULL, "Error: Map: More than 1 exit");
	visited = ft_matrix_dup(map->arr, map->row);
	flood_fill(map, visited, map->p_row, map->p_col);
	ft_free_triptr(&visited);
	if (!map->e_path)
		handle_map_error(map, NULL, "Error: Map: No valid path to exit");
	if (map->c_path != map->c_count)
		handle_map_error(map, 0, "Error: Map: No valid path to a collectible");
}

void	validate_map(t_map *map, int row, int col)
{
	while (++row < map->row)
	{
		if (row > 0 && (int)(ft_strlen(map->arr[row])) != map->col)
			handle_map_error(map, NULL, "Error: Map: Not rectangular");
		col = -1;
		while (++col < map->col)
		{
			if (map->arr[row][0] != '1' || map->arr[row][map->col -1] != '1'
				|| map->arr[0][col] != '1' || map->arr[map->row -1][col] != '1')
				handle_map_error(map, 0, "Error: Map: Not enclosed by walls");
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
