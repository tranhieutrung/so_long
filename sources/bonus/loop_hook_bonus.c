/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 21:31:10 by hitran            #+#    #+#             */
/*   Updated: 2024/08/22 11:33:36 by hitran           ###   ########.fr       */
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
		put_pixel(image, sprite->image, frame_index * PIXELS, 0);
		current_frame++;
		accumulator -= 0.083;
	}
}

static void	handle_game_running(t_solong *sl, double delta_time)
{
	update_object(sl->image[P], sl->sprite[P], delta_time);
	update_object(sl->image[C], sl->sprite[C], delta_time);
	update_object(sl->image[T], sl->sprite[T], delta_time);
}

void	loop_hook(void *param)
{
	t_solong	*sl;
	double		delta_time;

	sl = (t_solong *)param;
	delta_time = sl->mlx->delta_time;
	if (sl->state == RUN)
		handle_game_running(sl, delta_time);
}