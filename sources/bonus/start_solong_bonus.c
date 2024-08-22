/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_solong_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 00:30:53 by hitran            #+#    #+#             */
/*   Updated: 2024/08/22 14:37:09 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	move_player(t_solong *sl)
{
	image_to_window(sl, sl->image[S], sl->current.row, sl->current.col);
	ft_printf_fd(1, "Number of movements: %d\n", ++sl->moves);
	if (sl->map->arr[sl->next.row][sl->next.col] == 'C')
	{
		sl->map->arr[sl->current.row][sl->current.col] = '0';
		image_to_window(sl, sl->image[S], sl->next.row, sl->next.col);
		if (++sl->taken == sl->map->c_count)
			image_to_window(sl, sl->image[E],
				sl->map->exit.row, sl->map->exit.col);
	}
	else if (sl->next.row == sl->map->exit.row
		&& sl->next.col == sl->map->exit.col && sl->taken == sl->map->c_count)
	{
		ft_printf_fd(1, "You win!\n");
		sl->state = WIN;
	}
	else if (sl->map->arr[sl->next.row][sl->next.col] == 'T')
	{
		ft_printf_fd(1, "You lose!\n");
		sl->state = LOSE;
	}
	sl->map->arr[sl->current.row][sl->current.col] = '0';
	sl->map->arr[sl->next.row][sl->next.col] = 'P';
	image_to_window(sl, sl->image[P], sl->next.row, sl->next.col);
	sl->current = sl->next;
}

static void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_solong	*sl;

	sl = (t_solong *)param;
	if (keydata.action == MLX_PRESS)
	{
		if (keydata.key == MLX_KEY_ESCAPE)
			exit_solong(sl, EXIT_SUCCESS);
		if (sl->state != RUN)
			return ;
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

static void	init_solong(t_solong *sl)
{
	sl->width = sl->map->cols * PIXELS;
	sl->height = sl->map->rows * PIXELS;
	mlx_set_setting(MLX_STRETCH_IMAGE, 1);
	sl->mlx = mlx_init(sl->width, sl->height, "so_long", true);
	if (!sl->mlx)
		game_error(sl, mlx_strerror(mlx_errno));
	sl->current = sl->map->start;
	load_png(sl);
	display_map(sl, -1, -1);
}

void	start_solong(t_solong *sl)
{
	init_solong(sl);
	sl->moves = 0;
	mlx_key_hook(sl->mlx, key_hook, sl);
	mlx_loop_hook(sl->mlx, loop_hook, sl);
	mlx_close_hook(sl->mlx, close_hook, sl);
	mlx_loop(sl->mlx);
	exit_solong(sl, EXIT_SUCCESS);
}
