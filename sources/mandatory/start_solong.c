/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_solong.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 00:30:53 by hitran            #+#    #+#             */
/*   Updated: 2024/08/20 11:53:16 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	render_image(t_solong *sl, mlx_image_t *image, t_point current)
{
	if (mlx_image_to_window(sl->mlx, image, current.col * TEXTURE_SIZE,
			current.row * TEXTURE_SIZE) < 0)
		handle_game_error(sl, "cannot draw image to windows.");
}

static void	display_image(t_solong *sl, t_point current)
{
	if (sl->map->arr[current.row][current.col] == '0')
		render_image(sl, sl->image[0], current);
	else if (sl->map->arr[current.row][current.col] == '1')
		render_image(sl, sl->image[1], current);
	else if (sl->map->arr[current.row][current.col] == 'P')
	{
		render_image(sl, sl->image[0], current);
		render_image(sl, sl->image[2], current);
		sl->current = (t_point){current.row, current.col};
	}
	else if (sl->map->arr[current.row][current.col] == 'C')
	{
		render_image(sl, sl->image[0], current);
		render_image(sl, sl->image[3], current);
	}
	else if (sl->map->arr[current.row][current.col] == 'E')
	{
		render_image(sl, sl->image[0], current);
		sl->exit = (t_point){current.row, current.col};
	}
}

static mlx_image_t	*save_image(t_solong *sl, const char *path)
{
	mlx_texture_t	*texture;
	mlx_image_t		*image;

	texture = mlx_load_png(path);
	if (!texture)
		handle_game_error(sl, mlx_strerror(mlx_errno));
	image = mlx_texture_to_image(sl->mlx, texture);
	mlx_delete_texture(texture);
	if (!image)
		handle_game_error(sl, mlx_strerror(mlx_errno));
	if (!mlx_resize_image(image, TEXTURE_SIZE, TEXTURE_SIZE))
		handle_game_error(sl, mlx_strerror(mlx_errno));
	return (image);
}

static void	display_map(t_solong *sl)
{
	int32_t	row;
	int32_t	col;

	sl->image = malloc(TEXTURE_NUM * sizeof(mlx_image_t));
	if (!sl->image)
		handle_game_error(sl, "Allocation error on read texture.");
	sl->image[0] = save_image(sl, "./assets/textures/space.png");
	sl->image[1] = save_image(sl, "./assets/textures/wall.png");
	sl->image[2] = save_image(sl, "./assets/textures/player.png");
	sl->image[3] = save_image(sl, "./assets/textures/collectible.png");
	sl->image[4] = save_image(sl, "./assets/textures/exit.png");
	row = -1;
	while (++row < sl->map->rows)
	{
		col = -1;
		while (++col < sl->map->cols)
			display_image(sl, (t_point){row, col});
	}
}

void	start_solong(t_solong *sl)
{
	sl->width = sl->map->cols * TEXTURE_SIZE;
	sl->height = sl->map->rows * TEXTURE_SIZE;
	mlx_set_setting(MLX_STRETCH_IMAGE, 1);
	sl->mlx = mlx_init(sl->width, sl->height, "so_long", true);
	if (!sl->mlx)
		handle_game_error(sl, mlx_strerror(mlx_errno));
	display_map(sl);
	mlx_key_hook(sl->mlx, key_hook, sl);
	mlx_close_hook(sl->mlx, close_hook, sl);
	mlx_loop(sl->mlx);
	exit_solong(sl, EXIT_SUCCESS);
}
