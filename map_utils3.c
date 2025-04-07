/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samraoui <samraoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 11:52:29 by samraoui          #+#    #+#             */
/*   Updated: 2025/04/07 15:06:54 by samraoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	should_convert_to_wall(t_data *data, int i, int j)
{
	if (i == 0 || i == data->map_height - 1 || j == 0 || j == data->map_width
		- 1)
		return (1);
	if ((i + 1 < data->map_height && data->map[i + 1][j] == 0) || (i - 1 >= 0
			&& data->map[i - 1][j] == 0) || (j + 1 < data->map_width
			&& data->map[i][j + 1] == 0) || (j - 1 >= 0 && data->map[i][j
			- 1] == 0))
		return (1);
	return (0);
}

void	convert_spaces_to_walls(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->map_height)
	{
		j = 0;
		while (j < data->map_width)
		{
			if (data->map[i][j] == -3 && should_convert_to_wall(data, i, j))
				data->map[i][j] = 1;
			j++;
		}
		i++;
	}
}

void	fill_short_lines(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->map_height)
	{
		j = 0;
		while (j < data->map_width)
		{
			if (data->map[i][j] == -1)
				data->map[i][j] = -3;
			j++;
		}
		i++;
	}
}

int	validate_characters(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '0' && line[i] != '1' && line[i] != 'N' && line[i] != 'S'
			&& line[i] != 'E' && line[i] != 'W' && line[i] != ' '
			&& line[i] != '\n')
			return (ft_error("Invalid character in map"), 1);
		i++;
	}
	return (0);
}
