/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samraoui <samraoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 12:55:30 by doom              #+#    #+#             */
/*   Updated: 2025/04/07 14:58:37 by samraoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include <stdlib.h>
#include <unistd.h>

int	convert_char_to_int(char c, t_data *data, int x, int y)
{
	if (c == '0')
		return (0);
	else if (c == '1')
		return (1);
	else if (c == ' ')
		return (-3);
	else if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		set_player_position(data, c, x, y);
		return (0);
	}
	return (-1);
}

int	*convert_line_to_int(char *line, int width, t_data *data, int y)
{
	int	*line_int;
	int	i;
	int	j;

	line_int = malloc(sizeof(int) * width);
	if (!line_int)
		return (NULL);
	i = 0;
	j = 0;
	while (line[i] && line[i] != '\n')
	{
		line_int[j] = convert_char_to_int(line[i], data, j, y);
		i++;
		j++;
	}
	while (j < width)
	{
		line_int[j] = -3;
		j++;
	}
	return (line_int);
}

int	process_first_line(t_data *data, char *first_line, int *i)
{
	char	*line;

	line = ft_strdup(first_line);
	if (!line)
		return (0);
	data->map_width = get_map_width(line);
	data->map = malloc(sizeof(int *));
	if (!data->map)
	{
		free(line);
		return (0);
	}
	data->map[0] = convert_line_to_int(line, data->map_width, data, 0);
	if (!data->map[0])
	{
		free(line);
		free(data->map);
		return (0);
	}
	free(line);
	(*i)++;
	return (1);
}

int	handle_empty_line(char *line, int i, int *map_ended)
{
	if (i > 0)
		*map_ended = 1;
	free(line);
	return (1);
}

int	allocate_new_map_row(t_data *data, int i)
{
	int	**new_map;

	new_map = realloc(data->map, sizeof(int *) * (i + 1));
	if (!new_map)
		return (0);
	data->map = new_map;
	return (1);
}
