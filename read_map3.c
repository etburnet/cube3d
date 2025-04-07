/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samraoui <samraoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 12:55:40 by doom              #+#    #+#             */
/*   Updated: 2025/04/07 15:47:52 by samraoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include <stdlib.h>
#include <unistd.h>

static int	validate_map(t_data *data)
{
	if (data->pos_depart == '\0')
	{
		free_map(data->map, data->map_height);
		return (ft_error("No player spawn point"), 1);
	}
	if (!is_map_closed(data))
	{
		free_map(data->map, data->map_height);
		return (ft_error("Map is not closed by walls"), 1);
	}
	fill_short_lines(data);
	return (0);
}

static void	init_map_data(t_data *data)
{
	data->map_height = 0;
	data->map_width = 0;
	data->map = NULL;
	data->pos_depart = '\0';
}

static int	validate_temp_map(char **temp_map, int height, t_data *data)
{
	int	i;

	if (!temp_map)
		return (ft_error("Map reading error"), 1);
	i = 0;
	while (i < height)
	{
		if (validate_characters(temp_map[i]))
			return (free_temp_map(temp_map, height), 1);
		i++;
	}
	data->map_height = height;
	return (0);
}

static int	create_int_map(t_data *data, char **temp_map, int max_width)
{
	int	i;

	data->map_width = max_width;
	data->map = malloc(sizeof(int *) * data->map_height);
	if (!data->map)
		return (free_temp_map(temp_map, data->map_height),
			ft_error("Memory allocation failed"), 1);
	i = 0;
	while (i < data->map_height)
	{
		data->map[i] = convert_line_to_int(temp_map[i], max_width, data, i);
		if (!data->map[i])
		{
			free_map(data->map, i);
			return (1);
		}
		i++;
	}
	return (0);
}

int	get_map(int fd, t_data *data, char *first_line)
{
	char	**temp_map;
	int		max_width;
	int		height;

	init_map_data(data);
	temp_map = read_all_map_lines(fd, first_line, &height, &max_width);
	if (validate_temp_map(temp_map, height, data))
		return (1);
	if (create_int_map(data, temp_map, max_width))
	{
		free_temp_map(temp_map, height);
		return (ft_error("Map conversion error"), 1);
	}
	free_temp_map(temp_map, height);
	close(fd);
	return (validate_map(data));
}
