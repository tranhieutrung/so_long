/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 14:12:42 by hitran            #+#    #+#             */
/*   Updated: 2024/08/20 11:48:29 by hitran           ###   ########.fr       */
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
# define TEXTURE_SIZE 32

// MAX_COL = 3840 / TEXTURE_SIZE
# define MAX_COL 60

// MAX_ROW = 2160 / TEXTURE_SIZE
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
	int32_t	fd;
	int32_t	rows;
	int32_t	cols;
	int32_t	p_count;
	t_point	player;
	int32_t	e_count;
	int32_t	c_count;
	int32_t	c_paths;
	int32_t	e_paths;
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
	t_point		exit;
	int32_t		taken;
	int32_t		moves;
}	t_solong;

//		ALGORITHM	//

//		MAP			//
void	read_map(t_map *map, char *map_path);
void	start_solong(t_solong *sl);
void	move_player(t_solong *sl);
void	key_hook(mlx_key_data_t keydata, void *param);
void	close_hook(void *param);
//		UTILS		//
void	handle_file_error(t_map *map, char *map_path, char *message);
void	handle_map_error(t_map *map, char *message);
void	handle_game_error(t_solong *sl, const char *message);
void	exit_solong(t_solong *sl, int32_t stt);
void	render_image(t_solong *sl, mlx_image_t *image, t_point p);

#endif