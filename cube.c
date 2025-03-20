/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 14:18:07 by eburnet           #+#    #+#             */
/*   Updated: 2025/03/20 15:03:46 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void ft_init_side_dist(t_data *d)
{
	if(d->ray_dir_x < 0)
	{
		d->step_x = -1;
		d->side_dist_x = (d->pos_x - d->map_x) * d->delta_dist_x;
	}
	else
	{
		d->step_x = 1;
		d->side_dist_x = (d->map_x + 1.0 - d->pos_x) * d->delta_dist_x;
	}
	if(d->ray_dir_y < 0)
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

void ft_init_raycast(t_data *d, int x)
{
	d->cam_x = 2 * x / (double)d->screen_width - 1;
	d->ray_dir_x = d->dir_x + d->plane_x * d->cam_x;
	d->ray_dir_y = d->dir_y + d->plane_y * d->cam_x;
	d->map_x = (int)d->pos_x;
	d->map_y = (int)d->pos_y;
	if (d->ray_dir_x == 0)
		d->delta_dist_x = 1e30;
	else
		d->delta_dist_x = fabs(1/d->ray_dir_x);
	if (d->ray_dir_y == 0)
		d->delta_dist_y = 1e30;
	else
		d->delta_dist_y = fabs(1/d->ray_dir_y);
	ft_init_side_dist(d);
}

void ft_find_wall(t_data *d)
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
		if (d->map_x >= 0 && d->map_y >= 0)
			if (d->map_x < d->map_width && d->map_y < d->map_height)
				if (d->map[d->map_x][d->map_y] == 1)
					d->hit = 1;
	}
}

void ft_put_buff(t_data *d, int line_height, int tex_num, int x, int tex_x)
{
	int y;
	double step;
	int tex_y;
	double tex_pos;

	step = 1.0 * d->tex_height / line_height;
	tex_pos = (d->draw_start - d->screen_height + line_height / 2) * step;
	y = d->draw_start;
	while(y < d->draw_end)
	{
		tex_y = (int)tex_pos & (d->tex_height - 1);
		tex_pos += step;
		d->addr[y * (d->line_length / 4) + x] = d->textures[tex_num].pixels[tex_y * (d->tex_width) + tex_x];
		y++;
	}
}

void ft_draw(t_data *d, int line_height, int x)
{
	int tex_num;
	double wall_x;
	int tex_x;

	tex_num = d->map[d->map_x][d->map_y] - 1;
	if (d->side == 0)
		wall_x = d->pos_y + d->perp_wall_dist * d->ray_dir_y;
	else
		wall_x = d->pos_x + d->perp_wall_dist * d->ray_dir_x;
	wall_x -= floor((wall_x));
	tex_x = (int)(wall_x * (double)d->tex_width);
	if ((d->side == 0 && d->ray_dir_x > 0) || (d->side == 1 && d->ray_dir_y < 0))
		tex_x = d->tex_width - tex_x - 1;
	ft_put_buff(d, line_height, tex_num, x, tex_x);
}

void ft_dist_draw_points(t_data *d, int x)
{
	int line_height;
	
	if (d->side == 0)
		d->perp_wall_dist = d->side_dist_x - d->delta_dist_x;
	else
		d->perp_wall_dist = d->side_dist_y - d->delta_dist_y;
	line_height = (int)(d->screen_height / d->perp_wall_dist);
	d->draw_start = - line_height / 2 + d->screen_height / 2;
	if (d->draw_start < 0)
		d->draw_start = 0;
	d->draw_end = line_height / 2 + d->screen_height / 2;
	if (d->draw_end >= d->screen_height)
		d->draw_end = d->screen_height - 1;
	ft_draw(d, line_height, x); 
}

unsigned long createRGB(int r, int g, int b)
{   
    return ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
}

void ft_draw_fandc(t_data *d)
{
	int y;
	int x;

	y = 0;
	while (y < d->screen_height / 2)
	{
		x = 0;
		while (x < d->screen_width)
			d->addr[y * d->screen_width + x++] = createRGB(d->ceiling_color[0], d->ceiling_color[1], d->ceiling_color[2]);
		y++;
	}
	y = d->screen_height /2;
	while (y < d->screen_height)
	{
		x = 0;
		while (x < d->screen_width)
			d->addr[y * d->screen_width + x++] = createRGB(d->floor_color[0], d->floor_color[1], d->floor_color[2]);
		y++;
	}
} 

int ft_raycast(t_data *d)
{
	int x;

	x = 0;
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
