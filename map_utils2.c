/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samraoui <samraoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 11:50:29 by samraoui          #+#    #+#             */
/*   Updated: 2025/04/07 15:06:49 by samraoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	get_max_content_width(t_data *data)
{
	int	i;
	int	j;
	int	line_width;
	int	max_content_width;

	i = 0;
	max_content_width = 0;
	while (i < data->map_height)
	{
		line_width = 0;
		j = 0;
		while (j < data->map_width)
		{
			if (data->map[i][j] != -3)
				line_width = j + 1;
			j++;
		}
		if (line_width > max_content_width)
			max_content_width = line_width;
		i++;
	}
	return (max_content_width);
}

int	check_boundary_condition(t_data *data, int i, int j, int max_width)
{
	if (i == 0 || i == data->map_height - 1 || j == 0 || j == max_width - 1)
	{
		return (0);
	}
	return (1);
}

int	check_adjacent_spaces(t_data *data, int i, int j, int max_width)
{
	if ((j + 1 < max_width && data->map[i][j + 1] == -3) || (j - 1 >= 0
			&& data->map[i][j - 1] == -3) || (i + 1 < data->map_height
			&& data->map[i + 1][j] == -3) || (i - 1 >= 0 && data->map[i
			- 1][j] == -3))
	{
		return (0);
	}
	return (1);
}

int	check_map_boundaries(t_data *data, int max_content_width)
{
	int	i;
	int	j;
	int	valid;

	i = 0;
	valid = 1;
	while (i < data->map_height && valid)
	{
		j = 0;
		while (j < max_content_width && valid)
		{
			if (data->map[i][j] == 0)
			{
				valid = check_boundary_condition(data, i, j, max_content_width);
				if (valid)
					valid = check_adjacent_spaces(data, i, j,
							max_content_width);
			}
			j++;
		}
		i++;
	}
	return (valid);
}
