/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 15:54:32 by samraoui          #+#    #+#             */
/*   Updated: 2025/04/08 14:18:25 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	verify_parsing_complete(t_data *data, int map_found)
{
	int	i;

	i = 0;
	if (!check_textures_loaded(data) || !check_colors_loaded(data)
		|| !map_found)
	{
		while (i < 4)
		{
			if (data->texs[i].path)
				free(data->texs[i].path);
			i++;
		}
		return (ft_error("Missing map element"));
	}
	return (0);
}

void	free_temp_map(char **temp_map, int height)
{
	int	i;

	i = 0;
	while (i < height)
	{
		free(temp_map[i]);
		i++;
	}
	free(temp_map);
}

int	resize_temp_map(char ***temp_map, int *capacity, int current_size)
{
	char	**new_map;
	int		new_capacity;
	int		i;

	new_capacity = *capacity * 2;
	new_map = malloc(sizeof(char *) * new_capacity);
	if (!new_map)
		return (0);
	i = 0;
	while (i < current_size)
	{
		new_map[i] = (*temp_map)[i];
		i++;
	}
	free(*temp_map);
	*temp_map = new_map;
	*capacity = new_capacity;
	return (1);
}

int	handle_map_capacity(char ***temp_map, int *capacity, int i)
{
	if (i >= *capacity)
	{
		if (!resize_temp_map(temp_map, capacity, i))
			return (0);
	}
	return (1);
}
