/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 08:22:40 by hitran            #+#    #+#             */
/*   Updated: 2024/08/12 11:17:39 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	depth_first_search(t_map *map, char **visited, int x, int y)
{
	if (x < 1 || x >= map->row - 1 || y < 1 || y >= map->col - 1)
		return (0);
	if (map->target == 'C' && x == map->target_x && y == map->target_y)
		return (1);
	if (map->target == 'E' && map->arr[x][y] == 'E')
		return (1);
	if (map->arr[x][y] == '1' || visited[x][y] == '1')
		return (0);
	visited[x][y] = '1';
	if (depth_first_search(map, visited, x + 1, y)
		|| depth_first_search(map, visited, x - 1, y)
		|| depth_first_search(map, visited, x, y + 1)
		|| depth_first_search(map, visited, x, y - 1))
		return (1);
	return (0);
}

int	validate_path_to_target(t_map *map)
{
	char	**visited;
	int		res;
	int		i;

	visited = (char **)ft_calloc(map->row + 1, sizeof(char *));
	if (!visited)
		handle_map_error(map, NULL, "Error: Map: Memory allocation failed");
	i = -1;
	while (++i < map->row)
	{
		visited[i] = (char *)ft_calloc(map->col + 1, sizeof(char));
		if (!visited[i])
		{
			ft_free_triptr(&visited);
			handle_map_error(map, NULL, "Error: Map: Memory allocation failed");
		}
	}
	res = depth_first_search(map, visited, map->p_row, map->p_col);
	ft_free_triptr(&visited);
	return (res);
}

void	validate_path_to_objects(t_map *map)
{
	int	i;
	int	j;

	map->target = 'E';
	if (!validate_path_to_target(map))
		handle_map_error(map, NULL, "Error: Map: No valid path to exit");
	i = -1;
	while (++i < map->row)
	{
		j = -1;
		while (++j < map->col)
		{
			if (map->arr[i][j] != 'C')
				continue ;
			map->target = 'C';
			map->target_x = i;
			map->target_y = j;
			if (!validate_path_to_target(map))
				handle_map_error(map, NULL,
					"Error: Map: No valid path to a collectible");
		}
	}
}

void	validate_objects(t_map *map)
{
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
	validate_path_to_objects(map);
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
