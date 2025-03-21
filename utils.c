/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 14:26:20 by eburnet           #+#    #+#             */
/*   Updated: 2025/03/21 14:27:19 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	free_map(int **tab, int len)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (i < len && tab[i])
		free(tab[i++]);
	free(tab);
}

int	ft_x_close(t_data *data)
{
	mlx_destroy_image(data->mlx, data->img);
	mlx_destroy_image(data->mlx, data->no_texture);
	mlx_destroy_image(data->mlx, data->so_texture);
	mlx_destroy_image(data->mlx, data->ea_texture);
	mlx_destroy_image(data->mlx, data->we_texture);
	mlx_destroy_window(data->mlx, data->mlx_win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	free_map(data->map, data->map_height);
	exit(0);
	return (0);
}

int	ft_error(char *str)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
	return (1);
}
