/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 14:18:05 by eburnet           #+#    #+#             */
/*   Updated: 2025/04/08 13:33:15 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	ft_init_struct(t_data *data)
{
	data->screen_width = 640 * 1.5;
	data->screen_height = 480 * 1.5;
	data->tex_width = 64;
	data->tex_height = 64;
	data->hit = 0;
	data->keys.a = 0;
	data->keys.d = 0;
	data->keys.s = 0;
	data->keys.w = 0;
	data->keys.l_arrow = 0;
	data->keys.r_arrow = 0;
	return (0);
}

int	ft_init_image(t_data *d, int i)
{
	d->texs[0].tex = mlx_xpm_file_to_image(d->mlx, d->texs[0].path,
			&d->texs[0].tex_w, &d->texs[0].tex_h);
	if (!d->texs[0].tex)
		return (ft_error("\"NO\" image init"));
	d->texs[1].tex = mlx_xpm_file_to_image(d->mlx, d->texs[1].path,
			&d->texs[1].tex_w, &d->texs[1].tex_h);
	if (!d->texs[1].tex)
		return (ft_error("\"SO\" image init"));
	d->texs[2].tex = mlx_xpm_file_to_image(d->mlx, d->texs[2].path,
			&d->texs[2].tex_w, &d->texs[2].tex_h);
	if (!d->texs[2].tex)
		return (ft_error("\"EA\" image init"));
	d->texs[3].tex = mlx_xpm_file_to_image(d->mlx, d->texs[3].path,
			&d->texs[3].tex_w, &d->texs[3].tex_h);
	if (!d->texs[3].tex)
		return (ft_error("\"WE\" image init"));
	while (i < 4)
	{
		d->texs[i].pixels = (uint32_t *)mlx_get_data_addr(d->texs[i].tex,
				&d->texs[i].bpp, &d->texs[i].line_length, &d->texs[i].endian);
		if (d->texs[i].tex_w > 64 || d->texs[i].tex_h > 64)
			return (ft_error("Texture too big"));
		i++;
	}
	return (0);
}

void	ft_swap(t_data *data)
{
	double	tmp;
	double	tmp2;

	tmp = data->map_width;
	tmp2 = data->map_height;
	data->map_width = tmp2;
	data->map_height = tmp;
	tmp = data->pos_x;
	tmp2 = data->pos_y;
	data->pos_x = tmp2;
	data->pos_y = tmp;
}

int	ft_pars_init(t_data *data, char *argv1)
{
	if (ft_cub(argv1, data) >= 1)
		return (1);
	if (ft_init_struct(data))
		return (free_map(data->map, data->map_height), 1);
	ft_swap(data);
	data->mlx = mlx_init();
	if (data->mlx == NULL)
		return (ft_close(data), ft_error("mlx init failed"));
	data->mlx_win = mlx_new_window(data->mlx, data->screen_width,
			data->screen_height, "Cube3d");
	if (data->mlx_win == NULL)
		return (ft_close(data), ft_error("mlx new window failed"));
	return (0);
}

int	main(int argc, char *argv[])
{
	t_data	data;

	if (argc != 2)
		return (ft_error("Usage: ./cub3D <map_file>"));
	if (ft_pars_init(&data, argv[1]) == 1)
		return (1);
	mlx_hook(data.mlx_win, 02, 1L << 0, ft_key_press, &data);
	mlx_hook(data.mlx_win, 03, 1L << 1, ft_key_release, &data);
	mlx_hook(data.mlx_win, 17, 0, ft_x_close, &data);
	data.img = mlx_new_image(data.mlx, data.screen_width, data.screen_height);
	if (data.img == NULL)
		return (ft_close(&data), ft_error("mlx new image failed"));
	data.addr = (uint32_t *)mlx_get_data_addr(data.img, &data.bpp,
			&data.line_length, &data.endian);
	if (data.img == NULL)
		return (ft_close(&data), ft_error("mlx get data address failed"));
	if (ft_init_image(&data, 0) == 1)
		return (ft_close(&data), 1);
	mlx_loop_hook(data.mlx, ft_raycast, &data);
	mlx_loop(data.mlx);
	return (0);
}
