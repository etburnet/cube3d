/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mooves.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 13:16:16 by eburnet           #+#    #+#             */
/*   Updated: 2025/03/28 15:43:32 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	ft_rotate(t_data *d)
{
	double	rot_speed;
	double	old_dir_x;
	double	old_plane_x;

	rot_speed = 0.01;
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
		d->plane_x = d->plane_x * cos(-rot_speed) - d->plane_y
			* sin(-rot_speed);
		d->plane_y = old_plane_x * sin(-rot_speed) + d->plane_y
			* cos(-rot_speed);
	}
}

void	ft_av_ar(t_data *d)
{
	double	speed;

	speed = 0.01;
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
}

void	ft_ga_dr(t_data *d)
{
	double	speed;

	speed = 0.01;
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

int	ft_key_press(int keycode, t_data *d)
{
	if (keycode == 65307)
		ft_x_close(d);
	if (keycode == 'w')
		d->keys.w = 1;
	if (keycode == 's')
		d->keys.s = 1;
	if (keycode == 'd')
		d->keys.d = 1;
	if (keycode == 'a')
		d->keys.a = 1;
	if (keycode == 65363)
		d->keys.r_arrow = 1;
	if (keycode == 65361)
		d->keys.l_arrow = 1;
	return (0);
}

int	ft_key_release(int keycode, t_data *d)
{
	if (keycode == 'w')
		d->keys.w = 0;
	if (keycode == 's')
		d->keys.s = 0;
	if (keycode == 'd')
		d->keys.d = 0;
	if (keycode == 'a')
		d->keys.a = 0;
	if (keycode == 65363)
		d->keys.r_arrow = 0;
	if (keycode == 65361)
		d->keys.l_arrow = 0;
	return (0);
}
