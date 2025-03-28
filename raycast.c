/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 14:18:07 by eburnet           #+#    #+#             */
/*   Updated: 2025/03/28 16:36:59 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	ft_init_side_dist(t_data *d)
{
	if (d->ray_dir_x < 0)
	{
		d->step_x = -1;
		d->side_dist_x = (d->pos_x - d->map_x) * d->delta_dist_x;
	}
	else
	{
		d->step_x = 1;
		d->side_dist_x = (d->map_x + 1.0 - d->pos_x) * d->delta_dist_x;
	}
	if (d->ray_dir_y < 0)
	{
		d->step_y = -1;
		d->side_dist_y = (d->pos_y - d->map_y) * d->delta_dist_y;
	}
	else
	{
		d->step_y = 1;
		d->side_dist_y = (d->map_y + 1.0 - d->pos_y) * d->delta_dist_y;
	}
}

void	ft_find_wall(t_data *d)
{
	d->hit = 0;
	while (d->hit == 0)
	{
		if (d->side_dist_x < d->side_dist_y)
		{
			d->side_dist_x += d->delta_dist_x;
			d->map_x += d->step_x;
			d->side = 0;
		}
		else
		{
			d->side_dist_y += d->delta_dist_y;
			d->map_y += d->step_y;
			d->side = 1;
		}
		if (d->map[d->map_x][d->map_y] >= 1)
			d->hit = 1;
	}
}


void	ft_dist_draw_points(t_data *d, int x)
{
	int	line_height;

	if (d->side == 0)
		d->perp_wall_dist = d->side_dist_x - d->delta_dist_x;
	else
		d->perp_wall_dist = d->side_dist_y - d->delta_dist_y;
	line_height = (int)(d->screen_height / d->perp_wall_dist);
	d->draw_start = -line_height / 2 + d->screen_height / 2;
	if (d->draw_start < 0)
		d->draw_start = 0;
	d->draw_end = line_height / 2 + d->screen_height / 2;
	if (d->draw_end >= d->screen_height)
		d->draw_end = d->screen_height - 1;
	ft_wall(d, line_height, x);
}

void	ft_wall(t_data *d, int line_height, int x)
{
	double	wall_x;
	int		tex_x;

	if (d->side == 0)
		wall_x = d->pos_y + d->perp_wall_dist * d->ray_dir_y;
	else
		wall_x = d->pos_x + d->perp_wall_dist * d->ray_dir_x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * (double)d->tex_width);
	if ((d->side == 0 && d->ray_dir_x > 0) || (d->side == 1
			&& d->ray_dir_y < 0))
		tex_x = d->tex_width - tex_x - 1;
	ft_put_buff(d, line_height, x, tex_x);
}

void	ft_put_buff(t_data *d, int line_height, int x, int tex_x)
{
	int		tex_id;
	int		y;
	double	step;
	int		tex_y;
	double	tex_pos;

	tex_id = ft_textures(d);
	step = 1.0 * d->tex_height / line_height;
	tex_pos = (d->draw_start - d->screen_height / 2 + line_height / 2) * step;
	y = d->draw_start;
	while (y < d->draw_end)
	{
		tex_y = (int)tex_pos & (d->tex_height - 1);
		tex_pos += step;
		d->addr[y * (d->line_length / 4) + x] = d->textures[tex_id].pixels[tex_y
			* (d->tex_width) + tex_x];
		y++;
	}
}
