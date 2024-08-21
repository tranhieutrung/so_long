/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_map_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 00:30:53 by hitran            #+#    #+#             */
/*   Updated: 2024/08/21 15:03:06 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	image_to_window(t_solong *sl, mlx_image_t *im, int32_t row, int32_t col)
{
	if (mlx_image_to_window(sl->mlx, im, col * PIXELS, row * PIXELS) < 0)
		game_error(sl, mlx_strerror(mlx_errno));
}

// void sprite_to_window(t_solong *sl, t_sprite *sprite, int32_t row, int32_t col, int32_t frame)
// {
// 	int32_t frame_width;
// 	int32_t frame_height;
// 	int32_t x;
// 	int32_t y;

// 	frame_width = sprite->image->width / sprite->cols;
// 	frame_height = sprite->image->height / sprite->rows;
// 	x = (frame % sprite->cols) * frame_width;
// 	y = (frame / sprite->cols) * frame_height;
// 	if (mlx_image_to_window_region(sl->mlx, sprite->image, col * PIXELS, row * PIXELS, x, y, frame_width, frame_height) < 0)
// 		game_error(sl, mlx_strerror(mlx_errno));
// }

static int32_t	create_an_enemy(t_solong *sl, int32_t index, int32_t row, int32_t col)
{
	if (sl->map->arr[row][col] == '1')
		return (0);
	if (sl->map->arr[row][col] != '0')
	{
		if (create_an_enemy(sl, index, row + 1, col)
			|| create_an_enemy(sl, index, row - 1, col)
			|| create_an_enemy(sl, index, row, col + 1)
			|| create_an_enemy(sl, index, row, col - 1))
			return (1);
		else
			return (0);
	}
	else
	{
		sl->map->arr[row][col] = 'S';
		sl->enemies[index] = (t_point){row, col};
		return (1);
	}
}

static void	create_enemies(t_solong *sl, int32_t row, int32_t col)
{
	int32_t index;

	if (sl->map->c_count + 1 < sl->map->s_count)
		sl->enemie_num = sl->map->c_count + 1;
	else
		sl->enemie_num = sl->map->s_count;
	sl->enemies = (t_point *)ft_calloc(sl->enemie_num, sizeof(t_point));
	if (!sl->enemies)
		game_error(sl, "Memory allocation failed.");
	index = 0;
	while (++row < sl->map->rows - 1)
	{
		col = 0;
		while (++col < sl->map->cols - 1 && index < sl->enemie_num)
		{
			if (sl->map->arr[row][col] == 'C' || sl->map->arr[row][col] == 'E')
			{
				if(create_an_enemy(sl, index, row, col))
					index++;
			}
		}
	}
}

void	display_map(t_solong *sl, int32_t row, int32_t col)
{
	create_enemies(sl, 0, 0);
	while (++row < sl->map->rows)
	{
		col = -1;
		while (++col < sl->map->cols)
		{
			if (sl->map->arr[row][col] == '1')
				image_to_window(sl, sl->image[1], row, col);
			else
			{
				image_to_window(sl, sl->image[0], row, col);
				if (sl->map->arr[row][col] == 'P')
					image_to_window(sl, sl->sprite[0]->image, row, col);
				else if (sl->map->arr[row][col] == 'C')
					image_to_window(sl, sl->sprite[1]->image, row, col);
				else if (sl->map->arr[row][col] == 'S')
					image_to_window(sl, sl->sprite[2]->image, row, col);
				// if (sl->map->arr[row][col] == 'P')
				// 	sprite_to_window(sl, sl->sprite[0], row, col, 0);  // Player, frame 0
				// else if (sl->map->arr[row][col] == 'C')
				// 	sprite_to_window(sl, sl->sprite[1], row, col, 0);  // Collectible, frame 0
				// else if (sl->map->arr[row][col] == 'S')
				// 	sprite_to_window(sl, sl->sprite[2], row, col, 0);  // Enemy, frame 0
			}
		}
	}
}
