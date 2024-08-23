/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_solong_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 00:30:53 by hitran            #+#    #+#             */
/*   Updated: 2024/08/23 23:36:22 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	update_object(mlx_image_t *image, t_sprite *sprite, double delta_time)
{
	static double	accumulator = 0;
	static int32_t	current_frame = 0;
	int32_t			frame_index;

	accumulator += delta_time;
	frame_index = current_frame % sprite->cols;
	if (accumulator > 0.083)
	{
		put_pixel(image, sprite->image, frame_index * PX, 0);
		current_frame++;
		accumulator -= 0.083;
	}
}

void	loop_hook(void *param)
{
	t_solong	*sl;
	double		delta_time;

	sl = (t_solong *)param;
	delta_time = sl->mlx->delta_time;
	if (sl->state == RUNNING)
	{
		update_object(sl->image[P], sl->sprite[P], delta_time);
		update_object(sl->image[C], sl->sprite[C], delta_time);
		update_object(sl->image[T], sl->sprite[T], delta_time);
	}
}

static void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_solong	*sl;

	sl = (t_solong *)param;
	if (keydata.action == MLX_PRESS)
	{
		if (keydata.key == MLX_KEY_ESCAPE)
			exit_solong(sl, EXIT_SUCCESS);
		if (sl->state != RUNNING)
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

void	start_solong(t_solong *sl)
{
	sl->width = sl->map->cols * PX;
	sl->height = sl->map->rows * PX;
	mlx_set_setting(MLX_STRETCH_IMAGE, 1);
	sl->mlx = mlx_init(sl->width, sl->height, "so_long", true);
	if (!sl->mlx)
		game_error(sl, mlx_strerror(mlx_errno));
	sl->current = sl->map->start;
	load_png(sl);
	display_map(sl, -1, -1);
	sl->moves = 0;
	sl->state=RUNNING;
	sl->taken = 0;
	mlx_key_hook(sl->mlx, key_hook, sl);
	mlx_loop_hook(sl->mlx, loop_hook, sl);
	mlx_close_hook(sl->mlx, close_hook, sl);
	mlx_loop(sl->mlx);
	exit_solong(sl, EXIT_SUCCESS);
}
