/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 14:12:42 by hitran            #+#    #+#             */
/*   Updated: 2024/08/21 00:03:05 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "mylib.h"
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include "MLX42.h"
# define PIXELS 32

// MAX_COL = 3840 / PIXELS
# define MAX_COL 60

// MAX_ROW = 2160 / PIXELS
# define MAX_ROW 33
// BUFFER_SIZE  > MAX_COL * MAX_ROW
# define BUFFER_SIZE 2014
# define TEXTURE_NUM 5

typedef struct s_point
{
	int32_t	row;
	int32_t	col;
}	t_point;

typedef struct s_map
{
	char	**arr;
	int32_t	rows;
	int32_t	cols;
	int32_t	p_count;
	int32_t	e_count;
	int32_t	c_count;
	int32_t	c_paths;
	int32_t	e_paths;
	t_point	start;
	t_point	exit;
}	t_map;

typedef struct s_solong
{
	t_map		*map;
	mlx_t		*mlx;
	int32_t		width;
	int32_t		height;
	mlx_image_t	**image;
	t_point		current;
	t_point		next;
	int32_t		taken;
	int32_t		moves;
}	t_solong;

//		GAME		//
void	start_solong(t_solong *sl);
void	load_png_to_image(t_solong *sl);
void	display_map(t_solong *sl, int32_t row, int32_t col);
void	image_to_window(t_solong *sl, mlx_image_t *im, int32_t r, int32_t c);

//		MAP			//
void	read_map(t_map *map, int32_t fd);

//		UTILS		//
void	map_error(t_map *map, char *message);
void	game_error(t_solong *sl, const char *message);
void	exit_solong(t_solong *sl, int32_t stt);
void	count_objects(t_map *map, int32_t row, int32_t col);

#endif