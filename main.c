/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 14:17:25 by hitran            #+#    #+#             */
/*   Updated: 2024/08/12 11:10:40 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char **argv)
{
	t_map		map;

	if (argc != 2)
	{
		ft_printf_fd(2, "Error: Usage: ./so_long /[map_path]/[map_name].ber\n");
		return (1);
	}
	ft_bzero(&map, sizeof(map));
	read_map(&map, argv[1]);
	ft_free_triptr(&(map.arr));
	close(map.fd);
	return (0);
}
