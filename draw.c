/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 13:18:10 by eburnet           #+#    #+#             */
/*   Updated: 2025/03/28 13:23:22 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	ft_draw_fandc(t_data *d)
{
	int	y;
	int	x;

	y = 0;
	while (y < d->screen_height / 2)
	{
		x = 0;
		while (x < d->screen_width)
			d->addr[y * d->screen_width + x++] = create_rgb(d->ceiling_color[0],
					d->ceiling_color[1], d->ceiling_color[2]);
		y++;
	}
	y = d->screen_height / 2;
	while (y < d->screen_height)
	{
		x = 0;
		while (x < d->screen_width)
			d->addr[y * d->screen_width + x++] = create_rgb(d->floor_color[0],
					d->floor_color[1], d->floor_color[2]);
		y++;
	}
}

int	ft_textures(t_data *d)
{
	int	tex_id;

	tex_id = 0;
	if (d->side == 1)
	{
		if (d->step_y == -1)
			tex_id = 1;
		else if (d->step_y == 1)
			tex_id = 0;
	}
	else
	{
		if (d->step_x == -1)
			tex_id = 3;
		else if (d->step_x == 1)
			tex_id = 2;
	}
	return (tex_id);
}

int	ft_raycast(t_data *d)
{
	int	x;

	x = 0;
	ft_ga_dr(d);
	ft_av_ar(d);
	ft_rotate(d);
	ft_draw_fandc(d);
	while (x < d->screen_width)
	{
		ft_init_raycast(d, x);
		ft_find_wall(d);
		ft_dist_draw_points(d, x);
		x++;
	}
	mlx_put_image_to_window(d->mlx, d->mlx_win, d->img, 0, 0);
	return (0);
}
