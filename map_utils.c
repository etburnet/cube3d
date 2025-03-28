/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 17:10:29 by doom              #+#    #+#             */
/*   Updated: 2025/03/28 14:33:12 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	is_map_closed(t_data *data)
{
    int i;
    int j;
    
    i = 0;
    while (i < data->map_height)
    {
        j = 0;
        while (j < data->map_width)
        {
            if (data->map[i][j] == -3)
            {
                data->map[i][j] = 1;
            }
            if (data->map[i][j] == 0)
            {
                if (i == 0 || i == data->map_height - 1 || j == 0 || j == data->map_width - 1)
                    return (0);
                if (j + 1 < data->map_width && (data->map[i][j + 1] == -3))
                    return (0);
                if (j - 1 >= 0 && (data->map[i][j - 1] == -3))
                    return (0);
                if (i + 1 < data->map_height && (data->map[i + 1][j] == -3))
                    return (0);
                if (i - 1 >= 0 && (data->map[i - 1][j] == -3))
                    return (0);
            }
            j++;
        }
        i++;
    }
    return (1);
}

void	fill_short_lines(t_data *data)
{
    int i;
    int j;

    i = 0;
    while (i < data->map_height)
    {
        j = 0;
        while (j < data->map_width)
        {
            if (data->map[i][j] == -1)
                data->map[i][j] = -1;
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
		if (line[i] != '0' && line[i] != '1' && line[i] != 'N' && 
			line[i] != 'S' && line[i] != 'E' && line[i] != 'W' && 
			line[i] != ' ' && line[i] != '\n')
			return (ft_error("Invalid character in map"));
		i++;
	}
	return (1);
}
