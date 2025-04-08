/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 12:35:00 by doom              #+#    #+#             */
/*   Updated: 2025/04/08 10:08:19 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include <fcntl.h>

int	process_map_line(char *line, t_data *data, int fd, int *map_found)
{
	if (validate_characters(line) == 0)
	{
		*map_found = 1;
		if (get_map(fd, data, line) == 1)
			return (1);
		return (0);
	}
	else
	{
		free(line);
		close(fd);
		return (ft_error("Invalid map line format"), 1);
	}
}

int	handle_other_line(int fd)
{
	close(fd);
	return (ft_error("Invalid configuration format"), 1);
}

int	check_textures_loaded(t_data *data)
{
	if (!data->texs[0].path || !data->texs[1].path
		|| !data->texs[2].path || !data->texs[3].path)
		return (0);
	return (1);
}

int	check_colors_loaded(t_data *data)
{
	if (!data->floor_color_set || !data->ceiling_color_set)
		return (0);
	return (1);
}

int	check_config_complete(t_data *data)
{
	return (data->texs[0].path && data->texs[1].path
		&& data->texs[2].path && data->texs[3].path
		&& data->floor_color_set && data->ceiling_color_set);
}
