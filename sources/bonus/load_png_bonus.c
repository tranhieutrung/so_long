/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_png_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 00:30:53 by hitran            #+#    #+#             */
/*   Updated: 2024/08/27 13:10:39 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static mlx_image_t	*png_to_image(t_solong *sl, int32_t height,
	int32_t width, const char *path)
{
	mlx_texture_t	*texture;
	mlx_image_t		*image;

	if (path)
	{
		texture = mlx_load_png(path);
		if (!texture)
			game_error(sl, mlx_strerror(mlx_errno));
		image = mlx_texture_to_image(sl->mlx, texture);
		mlx_delete_texture(texture);
		if (!image)
			game_error(sl, mlx_strerror(mlx_errno));
		if (!mlx_resize_image(image, width, height))
			game_error(sl, mlx_strerror(mlx_errno));
	}
	else
	{
		image = mlx_new_image(sl->mlx, width, height);
		if (!image)
			game_error(sl, mlx_strerror(mlx_errno));
	}
	return (image);
}

static void	load_png_to_image(t_solong *sl)
{
	int32_t	size;

	sl->image = ft_calloc(PNG_TYPE + 1, sizeof(mlx_image_t));
	if (!sl->image)
		game_error(sl, "Memory allocation failed");
	sl->image[P] = png_to_image(sl, PX, PX, NULL);
	sl->image[C] = png_to_image(sl, PX, PX, NULL);
	sl->image[T] = png_to_image(sl, PX, PX, NULL);
	sl->image[E] = png_to_image(sl, PX, PX, T_EXIT);
	sl->image[O] = png_to_image(sl, PX, PX, T_OPEN);
	sl->image[S] = png_to_image(sl, PX, PX, T_SPACE);
	sl->image[W] = png_to_image(sl, PX, PX, T_WALL);
	size = 3 * PX;
	if (sl->map->cols < 9)
		size = sl->map->cols / 3;
	sl->image[WIN] = png_to_image(sl, size, 3 * size, T_WIN);
	sl->image[LOSE] = png_to_image(sl, size, 3 * size, T_LOSE);
	sl->image[M] = NULL;
}

static t_sprite	*png_to_sprite(t_solong *sl, const char *path,
	int32_t rows, int32_t cols)
{
	mlx_texture_t	*texture;
	t_sprite		*sprite;

	texture = mlx_load_png(path);
	if (!texture)
		game_error(sl, mlx_strerror(mlx_errno));
	sprite = (t_sprite *)ft_calloc(1, sizeof(t_sprite));
	if (!sprite)
		game_error(sl, "Memory allocation failed");
	sprite->image = mlx_texture_to_image(sl->mlx, texture);
	mlx_delete_texture(texture);
	if (!sprite->image)
		game_error(sl, mlx_strerror(mlx_errno));
	if (sprite->image->height / rows != PX)
	{
		if (!mlx_resize_image(sprite->image, cols * PX, rows * PX))
			game_error(sl, mlx_strerror(mlx_errno));
	}
	sprite->rows = rows;
	sprite->cols = cols;
	return (sprite);
}

static void	load_png_to_sprite(t_solong *sl)
{
	sl->sprite = ft_calloc(SPRITE_TYPE + 1, sizeof(t_sprite));
	if (!sl->sprite)
		game_error(sl, "Memory allocation failed");
	sl->sprite[P] = png_to_sprite(sl, S_PLAYER, 1, 12);
	sl->sprite[C] = png_to_sprite(sl, S_COLLECTIBLE, 1, 17);
	sl->sprite[T] = png_to_sprite(sl, S_TRAP, 1, 8);
}

void	load_png(t_solong *sl)
{
	load_png_to_image(sl);
	load_png_to_sprite(sl);
}
