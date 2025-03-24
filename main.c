/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 14:18:05 by eburnet           #+#    #+#             */
/*   Updated: 2025/03/24 10:35:17 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	ft_init_struct(t_data *data)
{
	int	i;

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
	// A supprimer apres ajout du parsing
	data->map_width = 13;
	data->map_height = 8;
	data->map = malloc(sizeof(int *) * data->map_height);
	i = 0;
	while (i < data->map_height)
	{
		data->map[i] = malloc(sizeof(int) * data->map_width);
		if (data->map[i] == NULL)
			return (free_map(data->map, data->map_height),
				ft_error("Malloc failed"));
		i++;
	}
	int template[8][13] = {
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
		{1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 0, 0, 1},
		{1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 1},
		{1, 0, 0, 1, 0, 0, 1, 1, 1, 0, 1, 0, 1},
		{1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	};
	for (int i = 0; i < data->map_height; i++)
		for (int j = 0; j < data->map_width; j++)
			data->map[i][j] = template[i][j];
	return (0);
}

void	ft_set_start(t_data *data)
{
	// gerer par parsing
	data->pos_y = 2;
	data->pos_x = 4;
	data->dir_x = -1;
	data->dir_y = 0;
	data->ceiling_color[0] = 7;
	data->ceiling_color[1] = 135;
	data->ceiling_color[2] = 227;
	data->floor_color[0] = 140;
	data->floor_color[1] = 143;
	data->floor_color[2] = 145;
}

int	ft_init_image(t_data *d)
{
	d->no_texture = mlx_xpm_file_to_image(d->mlx, "assets/NO.xpm",
			&d->tex_width, &d->tex_height);
	if (!d->no_texture)
		return (ft_error("NO image"));
	d->textures[0].pixels = (uint32_t *)mlx_get_data_addr(d->no_texture,
			&d->textures[0].bpp, &d->textures[0].line_length,
			&d->textures[0].endian);
	d->so_texture = mlx_xpm_file_to_image(d->mlx, "assets/SO.xpm",
			&d->tex_width, &d->tex_height);
	if (!d->so_texture)
		return (ft_error("SO image"));
	d->textures[1].pixels = (uint32_t *)mlx_get_data_addr(d->so_texture,
			&d->textures[1].bpp, &d->textures[1].line_length,
			&d->textures[1].endian);
	d->ea_texture = mlx_xpm_file_to_image(d->mlx, "assets/EA.xpm",
			&d->tex_width, &d->tex_height);
	if (!d->ea_texture)
		return (ft_error("EA image"));
	d->textures[2].pixels = (uint32_t *)mlx_get_data_addr(d->ea_texture,
			&d->textures[2].bpp, &d->textures[2].line_length,
			&d->textures[2].endian);
	d->we_texture = mlx_xpm_file_to_image(d->mlx, "assets/WE.xpm",
			&d->tex_width, &d->tex_height);
	if (!d->we_texture)
		return (ft_error("WE image"));
	d->textures[3].pixels = (uint32_t *)mlx_get_data_addr(d->we_texture,
			&d->textures[3].bpp, &d->textures[3].line_length,
			&d->textures[3].endian);
	return (0);
}

int	ft_key_press(int keycode, t_data *d)
{
	printf("ft_key_press\n");
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
	printf("ft_key_release\n");
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

int	main(void)
{
	t_data	data;

	if (ft_init_struct(&data))
		return (free_map(data.map, data.map_height), 1);
	ft_set_start(&data);
	data.mlx = mlx_init();
	data.mlx_win = mlx_new_window(data.mlx, data.screen_width,
			data.screen_height, "Cube3d");
	mlx_hook(data.mlx_win, 02, 1L << 0, ft_key_press, &data);
	mlx_hook(data.mlx_win, 03, 1L << 1, ft_key_release, &data);
	mlx_hook(data.mlx_win, 17, 0, ft_x_close, &data);
	data.img = mlx_new_image(data.mlx, data.screen_width, data.screen_height);
	data.addr = (uint32_t *)mlx_get_data_addr(data.img, &data.bpp,
			&data.line_length, &data.endian);
	if (ft_init_image(&data) == 1)
		return (1);
	mlx_loop_hook(data.mlx, ft_raycast, &data);
	mlx_loop(data.mlx);
	return (0);
}
