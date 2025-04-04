/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 14:18:05 by eburnet           #+#    #+#             */
/*   Updated: 2025/03/28 16:44:31 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	ft_init_struct(t_data *data)
{
	data->plane_x = 0;
	data->plane_y = 0.66;
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
	d->textures[0].tex = mlx_xpm_file_to_image(d->mlx, "assets/NO.xpm",
			&d->tex_width, &d->tex_height);
	if (!d->textures[0].tex)
		return (ft_error("NO image"));
	d->textures[1].tex = mlx_xpm_file_to_image(d->mlx, "assets/SO.xpm",
			&d->tex_width, &d->tex_height);
	if (!d->textures[1].tex)
		return (ft_error("SO image"));
	d->textures[2].tex = mlx_xpm_file_to_image(d->mlx, "assets/EA.xpm",
			&d->tex_width, &d->tex_height);
	if (!d->textures[2].tex)
		return (ft_error("EA image"));
	d->textures[3].tex = mlx_xpm_file_to_image(d->mlx, "assets/WE.xpm",
			&d->tex_width, &d->tex_height);
	if (!d->textures[3].tex)
		return (ft_error("WE image"));
	while (i < 4)
	{
		d->textures[i].pixels = (uint32_t *)mlx_get_data_addr(d->textures[i].tex,
			&d->textures[i].bpp, &d->textures[i].line_length,
			&d->textures[i].endian);
		i++;
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_data	data;

	if (argc != 2)
        return (ft_error("Usage: ./cub3D <map_file>"));
	if (ft_cub(argv[1], &data) >= 1)
		return (1);
	if (ft_init_struct(&data))
		return (free_map(data.map, data.map_height), 1);
	data.dir_x = -1;
	data.dir_y = 1;
	int tmp = data.map_width;
	int tmp2 = data.map_height;
	data.map_width = tmp2;
	data.map_height = tmp;
	tmp = data.pos_x;
	tmp2 = data.pos_y;
	data.pos_x = tmp2;
	data.pos_y = tmp;
	// printf("pos %f, %f\n", data.pos_x, data.pos_y);
	// printf("dir %f, %f\n", data.dir_x, data.dir_y);
	// printf("plane %f, %f\n", data.plane_x, data.plane_y);
	// printf("map size %d, %d\n", data.map_width, data.map_height);
	// print_parsed_data(&data);

	data.mlx = mlx_init();
	data.mlx_win = mlx_new_window(data.mlx, data.screen_width,
			data.screen_height, "Cube3d");
	mlx_hook(data.mlx_win, 02, 1L << 0, ft_key_press, &data);
	mlx_hook(data.mlx_win, 03, 1L << 1, ft_key_release, &data);
	mlx_hook(data.mlx_win, 17, 0, ft_x_close, &data);
	data.img = mlx_new_image(data.mlx, data.screen_width, data.screen_height);
	data.addr = (uint32_t *)mlx_get_data_addr(data.img, &data.bpp,
			&data.line_length, &data.endian);
	if (ft_init_image(&data, 0) == 1)
		return (1);
	mlx_loop_hook(data.mlx, ft_raycast, &data);
	mlx_loop(data.mlx);
	return (0);
}
