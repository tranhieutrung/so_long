/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_solong.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 00:30:53 by hitran            #+#    #+#             */
/*   Updated: 2024/08/27 13:06:08 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_solong	*sl;

	sl = (t_solong *)param;
	if (keydata.action == MLX_PRESS)
	{
		if (keydata.key == MLX_KEY_ESCAPE)
			exit_solong(sl, EXIT_SUCCESS);
		else if (keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_UP)
			sl->next = (t_point){sl->current.row - 1, sl->current.col};
		else if (keydata.key == MLX_KEY_S || keydata.key == MLX_KEY_DOWN)
			sl->next = (t_point){sl->current.row + 1, sl->current.col};
		else if (keydata.key == MLX_KEY_A || keydata.key == MLX_KEY_LEFT)
			sl->next = (t_point){sl->current.row, sl->current.col - 1};
		else if (keydata.key == MLX_KEY_D || keydata.key == MLX_KEY_RIGHT)
			sl->next = (t_point){sl->current.row, sl->current.col + 1};
		else
			return ;
		if (sl->map->arr[sl->next.row][sl->next.col] != '1')
			move_player(sl);
	}
}

static void	close_hook(void *param)
{
	exit_solong((t_solong *)param, EXIT_SUCCESS);
}

void	start_solong(t_solong *sl)
{
	mlx_set_setting(MLX_STRETCH_IMAGE, 1);
	sl->mlx = mlx_init(sl->map->cols * PX, sl->map->rows * PX, "so_long", true);
	if (!sl->mlx)
		game_error(sl, mlx_strerror(mlx_errno));
	sl->current = sl->map->start;
	load_png(sl);
	display_map(sl, -1, -1);
	mlx_key_hook(sl->mlx, key_hook, sl);
	mlx_close_hook(sl->mlx, close_hook, sl);
	mlx_loop(sl->mlx);
	exit_solong(sl, EXIT_SUCCESS);
}
