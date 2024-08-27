/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_png.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 00:30:53 by hitran            #+#    #+#             */
/*   Updated: 2024/08/27 13:05:06 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
	if (!mlx_resize_image(image, PX, PX))
		game_error(sl, mlx_strerror(mlx_errno));
	return (image);
}

void	load_png(t_solong *sl)
{
	sl->image = ft_calloc(PNG_TYPE + 1, sizeof(mlx_image_t));
	if (!sl->image)
		game_error(sl, "Memory allocation failed");
	sl->image[S] = png_to_image(sl, "./assets/textures/space.png");
	sl->image[W] = png_to_image(sl, "./assets/textures/wall.png");
	sl->image[P] = png_to_image(sl, "./assets/textures/player.png");
	sl->image[C] = png_to_image(sl, "./assets/textures/collectible.png");
	sl->image[E] = png_to_image(sl, "./assets/textures/exit.png");
	sl->image[O] = png_to_image(sl, "./assets/textures/open.png");
}
