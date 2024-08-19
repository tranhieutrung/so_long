/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_solong.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 00:30:53 by hitran            #+#    #+#             */
/*   Updated: 2024/08/20 00:30:55 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_tile(t_solong *sl)
{
	unsigned int	height;
	unsigned int	width;

	width = sl->width / sl->map->cols;
	height = sl->height / sl->map->rows;
	if (width <= height)
		sl->tile = width;
	else
		sl->tile = height;
}

void	draw_image(t_solong *sl, t_point p)
{
	if (sl->map->arr[p.row][p.col] == '0')
		add_image(sl, sl->image[0], p);
	else if (sl->map->arr[p.row][p.col] == '1')
		add_image(sl, sl->image[1], p);
	else if (sl->map->arr[p.row][p.col] == 'P')
	{
		add_image(sl, sl->image[0], p);
		add_image(sl, sl->image[2], p);
		sl->current.col = p.col;
		sl->current.row = p.row;
	}
	else if (sl->map->arr[p.row][p.col] == 'C')
	{
		add_image(sl, sl->image[0], p);
		add_image(sl, sl->image[3], p);
	}
	else if (sl->map->arr[p.row][p.col] == 'E')
	{
		add_image(sl, sl->image[0], p);
		sl->exit.col = p.col;
		sl->exit.row = p.row;
	}
}

static mlx_image_t	*load_image(t_solong *sl, const char *path)
{
	mlx_texture_t	*tex;
	mlx_image_t		*image;

	tex = mlx_load_png(path);
	if (!tex)
		handle_game_error(sl, "Failed to load image.");
	image = mlx_texture_to_image(sl->mlx, tex);
	mlx_delete_texture(tex);
	if (!image)
		handle_game_error(sl, "Allocation error on read texture.");
	if (!mlx_resize_image(image, sl->tile, sl->tile))
		handle_game_error(sl, "Failed to resize image.");
	return (image);
}

void	draw_map(t_solong *sl)
{
	int	row;
	int	col;

	check_tile(sl);
	sl->image = malloc(TEXTURE_NUM * sizeof(mlx_image_t));
	if (!sl->image)
		handle_game_error(sl, "Allocation error on read texture.");
	sl->image[0] = load_image(sl, "./assets/textures/space.png");
	sl->image[1] = load_image(sl, "./assets/textures/wall.png");
	sl->image[2] = load_image(sl, "./assets/textures/player.png");
	sl->image[3] = load_image(sl, "./assets/textures/collectible.png");
	sl->image[4] = load_image(sl, "./assets/textures/exit.png");
	row = -1;
	while (++row < sl->map->rows)
	{
		col = -1;
		while (++col < sl->map->cols)
			draw_image(sl, (t_point){row, col});
	}
}

void	start_solong(t_solong *sl)
{
	sl->width = sl->map->cols * TEXTURE_SIZE;
	sl->height = sl->map->rows * TEXTURE_SIZE;
	mlx_set_setting(MLX_STRETCH_IMAGE, 1);
	sl->mlx = mlx_init(sl->width, sl->height, "so_long", true);
	if (!sl->mlx)
		handle_game_error(sl, "Allocation error on initial graph.");
	draw_map(sl);
	mlx_key_hook(sl->mlx, key_hook, sl);
	mlx_close_hook(sl->mlx, close_hook, sl);
	mlx_loop(sl->mlx);
}
