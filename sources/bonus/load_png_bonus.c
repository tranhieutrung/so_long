/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_png_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 00:30:53 by hitran            #+#    #+#             */
/*   Updated: 2024/08/21 14:35:56 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static mlx_image_t	*png_to_image(t_solong *sl, const char *path)
{
	mlx_texture_t	*texture;
	mlx_image_t		*image;

	texture = mlx_load_png(path);
	if (!texture)
		game_error(sl, mlx_strerror(mlx_errno));
	image = mlx_texture_to_image(sl->mlx, texture);
	mlx_delete_texture(texture);
	if (!image)
		game_error(sl, mlx_strerror(mlx_errno));
	if (!mlx_resize_image(image, PIXELS, PIXELS))
		game_error(sl, mlx_strerror(mlx_errno));
	return (image);
}

static void	load_png_to_image(t_solong *sl)
{
	sl->image = ft_calloc(PNG_TYPE + 1, sizeof(mlx_image_t));
	if (!sl->image)
		game_error(sl, "Memory allocation failed");
	sl->image[0] = png_to_image(sl, "./assets/textures/space.png");
	sl->image[1] = png_to_image(sl, "./assets/textures/wall.png");
	sl->image[2] = png_to_image(sl, "./assets/textures/player.png");
	sl->image[3] = png_to_image(sl, "./assets/textures/collectible.png");
	sl->image[4] = png_to_image(sl, "./assets/textures/exit.png");
	sl->image[5] = png_to_image(sl, "./assets/textures/saw.png");
}

static t_sprite	*png_to_sprite(t_solong *sl, const char *path, int32_t rows, int32_t cols)
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
	if (!mlx_resize_image(sprite->image, PIXELS, PIXELS))
		game_error(sl, mlx_strerror(mlx_errno));
	sprite->rows = rows;
	sprite->cols = cols;
	return (sprite);
}

static void	load_png_to_sprite(t_solong *sl)
{
	sl->sprite = ft_calloc(SPRITE_TYPE + 1, sizeof(t_sprite));
	if (!sl->sprite)
		game_error(sl, "Memory allocation failed");
	sl->sprite[0] = png_to_sprite(sl, "./assets/sprite/ninja.png", 1, 12);
	sl->sprite[1] = png_to_sprite(sl, "./assets/sprite/cherries.png", 1, 17);
	sl->sprite[2] = png_to_sprite(sl, "./assets/sprite/saw.png", 1, 8);
}

void	load_png(t_solong *sl)
{
	load_png_to_image(sl);
	load_png_to_sprite(sl);
}
