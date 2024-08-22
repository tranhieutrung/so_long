/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_map_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 00:30:53 by hitran            #+#    #+#             */
/*   Updated: 2024/08/22 14:10:04 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	image_to_window(t_solong *sl, mlx_image_t *im, int32_t row, int32_t col)
{
	if (mlx_image_to_window(sl->mlx, im, col * PIXELS, row * PIXELS) < 0)
		game_error(sl, mlx_strerror(mlx_errno));
}

void	display_map(t_solong *sl, int32_t row, int32_t col)
{
	while (++row < sl->map->rows)
	{
		col = -1;
		while (++col < sl->map->cols)
		{
			if (sl->map->arr[row][col] == '1')
				image_to_window(sl, sl->image[W], row, col);
			else
			{
				image_to_window(sl, sl->image[S], row, col);
				if (sl->map->arr[row][col] == 'P')
					image_to_window(sl, sl->image[P], row, col);
				else if (sl->map->arr[row][col] == 'C')
					image_to_window(sl, sl->image[C], row, col);
				else if (sl->map->arr[row][col] == 'T')
					image_to_window(sl, sl->image[T], row, col);
			}
		}
	}
}
