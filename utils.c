/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 14:26:20 by eburnet           #+#    #+#             */
/*   Updated: 2025/04/08 13:34:50 by eburnet          ###   ########.fr       */
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
	int	i;

	i = 0;
	if (data->img)
		mlx_destroy_image(data->mlx, data->img);
	while (i < 4)
	{
		if (data->texs[i].tex)
			mlx_destroy_image(data->mlx, data->texs[i].tex);
		free(data->texs[i].path);
		i++;
	}
	if (data->mlx_win)
		mlx_destroy_window(data->mlx, data->mlx_win);
	if (data->mlx)
		mlx_destroy_display(data->mlx);
	if (data->mlx)
		free(data->mlx);
	free_map(data->map, data->map_width);
	exit(0);
	return (0);
}

void	ft_close(t_data *data)
{
	int	i;

	i = 0;
	if (data->img)
		mlx_destroy_image(data->mlx, data->img);
	while (i < 4)
	{
		if (data->texs[i].tex)
			mlx_destroy_image(data->mlx, data->texs[i].tex);
		free(data->texs[i].path);
		i++;
	}
	if (data->mlx_win)
		mlx_destroy_window(data->mlx, data->mlx_win);
	if (data->mlx)
		mlx_destroy_display(data->mlx);
	if (data->mlx)
		free(data->mlx);
	free_map(data->map, data->map_width);
	exit(1);
}

int	ft_error(char *str)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
	return (1);
}

void	ft_init_raycast(t_data *d, int x)
{
	d->cam_x = 2 * x / (double)d->screen_width - 1;
	d->ray_dir_x = d->dir_x + d->plane_x * d->cam_x;
	d->ray_dir_y = d->dir_y + d->plane_y * d->cam_x;
	d->map_x = (int)d->pos_x;
	d->map_y = (int)d->pos_y;
	if (d->ray_dir_x == 0)
		d->delta_dist_x = 1e30;
	else
		d->delta_dist_x = fabs(1 / d->ray_dir_x);
	if (d->ray_dir_y == 0)
		d->delta_dist_y = 1e30;
	else
		d->delta_dist_y = fabs(1 / d->ray_dir_y);
	ft_init_side_dist(d);
}
