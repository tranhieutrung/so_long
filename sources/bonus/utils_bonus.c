/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 14:17:25 by hitran            #+#    #+#             */
/*   Updated: 2024/08/21 21:07:10 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void free_sprite(t_solong *sl)
{
	int32_t	index;

	if (!sl)
		return ;
	if (sl->sprite)
	{
		index = -1;
		while (++index < PNG_TYPE && sl->sprite[index])
		{
			mlx_delete_image(sl->mlx, sl->sprite[index]->image);
			free(sl->sprite[index]);
		}
		free(sl->sprite);
	}
}

void	exit_solong(t_solong *sl, int32_t status)
{
	int32_t	index;

	if (!sl)
		return ;
	if (sl->map && sl->map->arr)
		ft_free_triptr(&sl->map->arr);
	if (sl->image)
	{
		index = -1;
		while (++index < PNG_TYPE && sl->image[index])
			mlx_delete_image(sl->mlx, sl->image[index]);
		free(sl->image);
	}
	free_sprite(sl);
	if (sl->mlx)
		mlx_terminate(sl->mlx);
	exit (status);
}

void	map_error(t_map *map, char *message)
{
	if (map && map->arr)
		ft_free_triptr(&map->arr);
	ft_printf_fd(2, "Error\nMap: %s\n", message);
	exit (EXIT_FAILURE);
}

void	game_error(t_solong *sl, const char *message)
{
	ft_printf_fd(2, "Error\nGame: %s\n", message);
	exit_solong(sl, EXIT_FAILURE);
}

void	count_objects(t_map *map, int32_t row, int32_t col)
{
	if (map->arr[row][col] == '0')
		map->s_count++;
	if (map->arr[row][col] == 'P')
	{
		map->p_count++;
		map->start = (t_point){row, col};
	}
	else if (map->arr[row][col] == 'C')
		map->c_count++;
	else if (map->arr[row][col] == 'E')
	{
		map->e_count++;
		map->exit = (t_point){row, col};
	}
}