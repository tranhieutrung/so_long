/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 23:50:48 by hitran            #+#    #+#             */
/*   Updated: 2024/08/20 11:57:32 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	move_player(t_solong *sl)
{
	render_image(sl, sl->image[0], sl->current);
	if (sl->map->arr[sl->next.row][sl->next.col] == 'C')
	{
		sl->map->arr[sl->current.row][sl->current.col] = '0';
		sl->taken++;
		render_image(sl, sl->image[0], sl->next);
		if (sl->taken == sl->map->c_count)
			render_image(sl, sl->image[4], sl->exit);
	}
	else if (sl->next.row == sl->exit.row && sl->next.col == sl->exit.col
		&& sl->taken == sl->map->c_count)
	{
		ft_printf_fd(1, "Moves: %u, Collectibles: %u\n",
			++sl->moves, sl->taken);
		ft_printf_fd(1, "You win!\n");
		exit_solong(sl, EXIT_SUCCESS);
	}
	sl->map->arr[sl->current.row][sl->current.col] = '0';
	sl->map->arr[sl->next.row][sl->next.col] = 'P';
	ft_printf_fd(1, "Moves: %u, Collectibles: %u\n", ++sl->moves, sl->taken);
	render_image(sl, sl->image[2], sl->next);
	sl->current = sl->next;
}

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_solong	*sl;

	sl = (t_solong *)param;
	if (keydata.action == MLX_PRESS)
	{
		if (keydata.key == MLX_KEY_ESCAPE)
			exit_solong(sl, EXIT_SUCCESS);
		else if (keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_UP)
			sl->next = (t_point){sl->current.row - 1, sl->current.col};
		else if (keydata.key == MLX_KEY_S || keydata.key == MLX_KEY_DOWN)
			sl->next = (t_point){sl->current.row + 1, sl->current.col};
		else if (keydata.key == MLX_KEY_A || keydata.key == MLX_KEY_LEFT)
			sl->next = (t_point){sl->current.row, sl->current.col - 1};
		else if (keydata.key == MLX_KEY_D || keydata.key == MLX_KEY_RIGHT)
			sl->next = (t_point){sl->current.row, sl->current.col + 1};
		else
			return ;
		if (sl->map->arr[sl->next.row][sl->next.col] == '1')
			ft_printf_fd(1, "Can not go through walls\n");
		else
			move_player(sl);
	}
}

void	close_hook(void *param)
{
	exit_solong((t_solong *)param, EXIT_SUCCESS);
}
