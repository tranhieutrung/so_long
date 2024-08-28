/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_png.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 00:30:53 by hitran            #+#    #+#             */
/*   Updated: 2024/08/28 09:24:55 by hitran           ###   ########.fr       */
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
	sl->image[S] = png_to_image(sl, T_SPACE);
	sl->image[W] = png_to_image(sl, T_WALL);
	sl->image[P] = png_to_image(sl, T_PLAYER);
	sl->image[C] = png_to_image(sl, T_COLLECTIBLE);
	sl->image[E] = png_to_image(sl, T_EXIT);
	sl->image[O] = png_to_image(sl, T_OPEN);
}
