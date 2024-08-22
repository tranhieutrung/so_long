/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixel_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 22:21:03 by hitran            #+#    #+#             */
/*   Updated: 2024/08/21 22:52:32 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

/**
 * In MLX42 Colors are as follows:
 * 0000 0000 A (1st byte) -> uint8_t because it's 8 bits
 * 0000 0000 R (2nd byte)
 * 0000 0000 G (3rd byte)
 * 0000 0000 B (4th byte)
 **/
static int32_t	get_pixel(mlx_image_t *image, uint32_t x, uint32_t y)
{
	uint8_t	*pixelstart;

	if (x > image->width || y > image->height)
		return (0xFF000000);
	pixelstart = image->pixels + (y * image->width + x) * sizeof(int32_t);
	return (get_rgba(*(pixelstart), *(pixelstart + 1), *(pixelstart + 2),
		*(pixelstart + 3)));
}

void	put_pixel(mlx_image_t *img, mlx_image_t *sprite, int32_t x, int32_t y)
{
	uint32_t	w;
	uint32_t	h;

	h = 0;
	while (h < img->height)
	{
		w = 0;
		while (w < img->width)
		{
			mlx_put_pixel(img, w, h, get_pixel(sprite, x + w, y + h));
			w++;
		}
		h++;
	}
}
