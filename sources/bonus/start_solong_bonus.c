/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_solong_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 00:30:53 by hitran            #+#    #+#             */
/*   Updated: 2024/08/28 11:44:41 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	put_pixel(mlx_image_t *img, mlx_image_t *spt, int32_t x, int32_t y)
{
	uint32_t	w;
	uint32_t	h;
	uint8_t		*px;
	int32_t		color;

	h = 0;
	while (h < img->height)
	{
		w = 0;
		while (w < img->width)
		{
			if (x + w > spt->width || y + h > spt->height)
				color = 0xFF000000;
			px = spt->pixels + ((y + h) * spt->width + x + w) * sizeof(int32_t);
			color = *px << 24 | *(px + 1) << 16 | *(px + 2) << 8 | *(px + 3);
			mlx_put_pixel(img, w, h, color);
			w++;
		}
		h++;
	}
}

static void	loop_hook(void *param)
{
	t_solong	*sl;
	int32_t		p_frame;
	int32_t		c_frame;
	int32_t		t_frame;

	sl = (t_solong *)param;
	if (sl->state == RUNNING)
	{
		sl->time += sl->mlx->delta_time;
		p_frame = sl->current_frame % sl->sprite[P]->cols;
		c_frame = sl->current_frame % sl->sprite[C]->cols;
		t_frame = sl->current_frame % sl->sprite[T]->cols;
		if (sl->time > 0.0833)
		{
			put_pixel(sl->image[P], sl->sprite[P]->image, p_frame * PX, 0);
			put_pixel(sl->image[C], sl->sprite[C]->image, c_frame * PX, 0);
			put_pixel(sl->image[T], sl->sprite[T]->image, t_frame * PX, 0);
			sl->current_frame++;
			sl->time -= 0.0833;
		}
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
	t_solong	*sl;

	sl = (t_solong *)param;
	mlx_close_window(sl->mlx);
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
	mlx_loop_hook(sl->mlx, loop_hook, sl);
	mlx_close_hook(sl->mlx, close_hook, sl);
	mlx_loop(sl->mlx);
	exit_solong(sl, EXIT_SUCCESS);
}
