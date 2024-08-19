/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 14:17:25 by hitran            #+#    #+#             */
/*   Updated: 2024/08/20 00:32:48 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	handle_file_error(t_map *map, char *map_path, char *message)
{
	if (map && map->fd > 2)
		close(map->fd);
	ft_printf_fd(2, "Error\n%s: %s\n", map_path, message);
	exit (1);
}

void	handle_map_error(t_map *map, char *message)
{
	if (map && map->arr)
		ft_free_triptr(&map->arr);
	if (map && map->fd > 2)
		close(map->fd);
	ft_printf_fd(2, "Error\nMap: %s\n", message);
	exit (1);
}

void	handle_game_error(t_solong *sl, char *message)
{
	ft_printf_fd(2, "Error\nGame: %s\n", message);
	exit_solong(sl, 1);
}

void	exit_solong(t_solong *sl, int stt)
{
	int	i;

	if (!sl)
		return ;
	if (sl->image)
	{
		i = -1;
		while (++i < TEXTURE_NUM)
			mlx_delete_image(sl->mlx, sl->image[i]);
		free(sl->image);
	}
	if (sl->map && sl->map->arr)
		ft_free_triptr(&sl->map->arr);
	if (sl->map && sl->map->fd > 2)
		close(sl->map->fd);
	if (sl->mlx)
		mlx_terminate(sl->mlx);
	exit (stt);
}

void	add_image(t_solong *sl, mlx_image_t *image, t_point p)
{
	if (mlx_image_to_window(sl->mlx, image, p.col * sl->tile,
			p.row * sl->tile) < 0)
		handle_game_error(sl, "cannot draw image to windows.");
}
