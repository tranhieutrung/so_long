/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 23:31:52 by hitran            #+#    #+#             */
/*   Updated: 2024/08/28 11:34:02 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static t_point	calculate_position(t_solong *sl)
{
	if (sl->map->cols < 6)
		return ((t_point){(sl->map->rows - 1) / 2, (sl->map->cols - 3) / 2});
	else if (sl->map->cols >= 6 && sl->map->cols < 9)
		return ((t_point){(sl->map->rows - 2) / 2, (sl->map->cols - 6) / 2});
	else
		return ((t_point){(sl->map->rows - 3) / 2, (sl->map->cols - 9) / 2});
}

static void	print_state(t_solong *sl)
{
	char	*nbr;
	t_point	position;
	int32_t	move_pst;

	nbr = ft_itoa(++sl->moves);
	if (sl->moves <= 9)
		move_pst = PX * 2 / 5;
	else if (sl->moves > 9 && sl->moves < 100)
		move_pst = PX / 3;
	else
		move_pst = PX / 4;
	mlx_delete_image(sl->mlx, sl->image[M]);
	sl->image[M] = mlx_put_string(sl->mlx, nbr,
			sl->current.col * PX + move_pst, sl->current.row * PX - PX / 3);
	if (!sl->image[M])
		game_error(sl, mlx_strerror(mlx_errno));
	position = calculate_position(sl);
	if (sl->state == WON)
		image_to_window(sl, sl->image[WIN], position.row, position.col);
	else if (sl->state == LOST)
		image_to_window(sl, sl->image[LOSE], position.row, position.col);
	free(nbr);
}

static void	disable_current_collectible(t_solong *sl)
{
	int32_t	i;

	i = 0;
	while (i < sl->map->c_count)
	{
		if (sl->image[C]->instances[i].x == sl->current.col * PX
			&& sl->image[C]->instances[i].y == sl->current.row * PX)
		{
			sl->image[C]->instances[i].enabled = false;
			break ;
		}
		i++;
	}
}

void	move_player(t_solong *sl)
{
	sl->current = sl->next;
	if (sl->map->arr[sl->current.row][sl->current.col] == 'C')
	{
		sl->map->arr[sl->current.row][sl->current.col] = '0';
		disable_current_collectible(sl);
		sl->taken++;
		if (sl->taken == sl->map->c_count)
			sl->image[E]->instances[0].enabled = false;
	}
	else if (sl->map->arr[sl->current.row][sl->current.col] == 'E'
		&& sl->taken == sl->map->c_count)
		sl->state = WON;
	else if (sl->map->arr[sl->current.row][sl->current.col] == 'T')
		sl->state = LOST;
	sl->image[P]->instances[0].x = sl->current.col * PX;
	sl->image[P]->instances[0].y = sl->current.row * PX;
	print_state(sl);
}
