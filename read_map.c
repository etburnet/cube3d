/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 15:50:50 by doom              #+#    #+#             */
/*   Updated: 2025/04/08 14:18:35 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include <stdlib.h>
#include <unistd.h>

int	get_map_width(char *line)
{
	int	width;
	int	i;

	i = 0;
	width = 0;
	while (line[i] && line[i] != '\n')
	{
		width++;
		i++;
	}
	return (width);
}

static void	init_direction_n_s(t_data *data, char c)
{
	if (c == 'N')
	{
		data->dir_x = -1;
		data->dir_y = 0;
		data->plane_x = 0;
		data->plane_y = 0.66;
	}
	else if (c == 'S')
	{
		data->dir_x = 1;
		data->dir_y = 0;
		data->plane_x = 0;
		data->plane_y = -0.66;
	}
}

static void	init_direction_e_w(t_data *data, char c)
{
	if (c == 'E')
	{
		data->dir_x = 0;
		data->dir_y = 1;
		data->plane_x = 0.66;
		data->plane_y = 0;
	}
	else if (c == 'W')
	{
		data->dir_x = 0;
		data->dir_y = -1;
		data->plane_x = -0.66;
		data->plane_y = 0;
	}
}

int	set_player_position(t_data *data, char c, int x, int y)
{
	if (data->pos_depart != '\0')
		return (ft_error("Multiple player spawn points"));
	data->pos_depart = c;
	data->pos_x = x + 0.5;
	data->pos_y = y + 0.5;
	if (c == 'N' || c == 'S')
		init_direction_n_s(data, c);
	else if (c == 'E' || c == 'W')
		init_direction_e_w(data, c);
	return (0);
}
