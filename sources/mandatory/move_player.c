/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 13:03:44 by hitran            #+#    #+#             */
/*   Updated: 2024/08/27 13:05:42 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	off_collectible(t_solong *sl)
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
	ft_printf_fd(1, "Number of movements: %d\n", ++sl->moves);
	if (sl->map->arr[sl->current.row][sl->current.col] == 'C')
	{
		sl->map->arr[sl->current.row][sl->current.col] = '0';
		off_collectible(sl);
		sl->taken++;
		if (sl->taken == sl->map->c_count)
			sl->image[E]->instances[0].enabled = false;
	}
	else if (sl->map->arr[sl->current.row][sl->current.col] == 'E'
		&& sl->taken == sl->map->c_count)
	{
		ft_printf_fd(1, "You win!\n");
		exit_solong(sl, EXIT_SUCCESS);
	}
	sl->image[P]->instances[0].x = sl->current.col * PX;
	sl->image[P]->instances[0].y = sl->current.row * PX;
}
