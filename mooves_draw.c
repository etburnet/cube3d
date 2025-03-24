/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mooves_draw.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 13:18:10 by eburnet           #+#    #+#             */
/*   Updated: 2025/03/24 10:46:58 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

unsigned long	createRGB(int r, int g, int b)
{
	return ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
}

void	ft_draw_fandc(t_data *d)
{
	int	y;
	int	x;

	y = 0;
	while (y < d->screen_height / 2)
	{
		x = 0;
		while (x < d->screen_width)
			d->addr[y * d->screen_width + x++] = createRGB(d->ceiling_color[0],
					d->ceiling_color[1], d->ceiling_color[2]);
		y++;
	}
	y = d->screen_height / 2;
	while (y < d->screen_height)
	{
		x = 0;
		while (x < d->screen_width)
			d->addr[y * d->screen_width + x++] = createRGB(d->floor_color[0],
					d->floor_color[1], d->floor_color[2]);
		y++;
	}
}

void	ft_mooves(t_data *d)
{
	double	speed;

	speed = 0.1;
	if (d->keys.w == 1)
	{
		if (d->map[(int)(d->pos_x + d->dir_x * speed)][(int)d->pos_y] == 0)
			d->pos_x += d->dir_x * speed;
		if (d->map[(int)d->pos_x][(int)(d->pos_y + d->dir_y * speed)] == 0)
			d->pos_y += d->dir_y * speed;
	}
	if (d->keys.s == 1)
	{
		if (d->map[(int)(d->pos_x - d->dir_x * speed)][(int)d->pos_y] == 0)
			d->pos_x -= d->dir_x * speed;
		if (d->map[(int)d->pos_x][(int)(d->pos_y - d->dir_y * speed)] == 0)
			d->pos_y -= d->dir_y * speed;
	}
	if (d->keys.a == 1)
	{
		if (d->map[(int)(d->pos_x - d->plane_x * speed)][(int)d->pos_y] == 0)
			d->pos_x -= d->plane_x * speed;
		if (d->map[(int)d->pos_x][(int)(d->pos_y - d->plane_y * speed)] == 0)
			d->pos_y -= d->plane_y * speed;
	}
	if (d->keys.d == 1)
	{
		if (d->map[(int)(d->pos_x + d->plane_x * speed)][(int)d->pos_y] == 0)
			d->pos_x += d->plane_x * speed;
		if (d->map[(int)d->pos_x][(int)(d->pos_y + d->plane_y * speed)] == 0)
			d->pos_y += d->plane_y * speed;
	}
}

void	ft_rotate(t_data *d)
{
	double	rot_speed;
	double	old_dir_x;
	double	old_plane_x;

	rot_speed = 0.1;
	if (d->keys.l_arrow == 1)
	{
		old_dir_x = d->dir_x;
		d->dir_x = d->dir_x * cos(rot_speed) - d->dir_y * sin(rot_speed);
		d->dir_y = old_dir_x * sin(rot_speed) + d->dir_y * cos(rot_speed);

		old_plane_x = d->plane_x;
		d->plane_x = d->plane_x * cos(rot_speed) - d->plane_y * sin(rot_speed);
		d->plane_y = old_plane_x * sin(rot_speed) + d->plane_y * cos(rot_speed);
	}
	if (d->keys.r_arrow == 1)
	{
		old_dir_x = d->dir_x;
		d->dir_x = d->dir_x * cos(-rot_speed) - d->dir_y * sin(-rot_speed);
		d->dir_y = old_dir_x * sin(-rot_speed) + d->dir_y * cos(-rot_speed);

		old_plane_x = d->plane_x;
		d->plane_x = d->plane_x * cos(-rot_speed) - d->plane_y * sin(-rot_speed);
		d->plane_y = old_plane_x * sin(-rot_speed) + d->plane_y * cos(-rot_speed);
	}
}

int	ft_textures(t_data *d)
{
	int tex_id;

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
	int x;

	x = 0;
	ft_mooves(d);
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