/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 14:12:42 by hitran            #+#    #+#             */
/*   Updated: 2024/08/16 14:48:03 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "mylib.h"
# include <stdio.h>
# include <fcntl.h>

// Render pixels = 64
// MAX_COL = 3840 / 64
// MAX_ROW = 2160 / 64
# define MAX_COL 44
# define MAX_ROW 26

typedef struct s_map
{
	char	**arr;
	int		fd;
	int		row;
	int		col;
	int		p_count;
	int		e_count;
	int		c_count;
	int		p_row;
	int		p_col;
	int		c_path;
	int		e_path;
}	t_map;

// typedef struct s_solong
// {
// 	t_map	*map;
// 	mlx_t	mlx;
// }	t_solong;
//		ALGORITHM	//

//		MAP			//
void	read_map(t_map *map, char *map_path);
void	validate_map(t_map *map, int row, int col);

//		UTILS		//
void	handle_map_error(t_map *map, char *line, char *message);

#endif