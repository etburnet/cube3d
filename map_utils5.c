/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samraoui <samraoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 11:57:29 by samraoui          #+#    #+#             */
/*   Updated: 2025/04/07 16:07:24 by samraoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static int	handle_line(char ***temp_map, int *capacity, int i, char *line)
{
	if (!handle_map_capacity(temp_map, capacity, i))
	{
		free_temp_map(*temp_map, i);
		free(line);
		return (0);
	}
	return (1);
}

static int	process_line_content(char **temp_map, char *line, int i,
		int *max_width)
{
	return (add_line_to_map(temp_map, line, i, max_width));
}

static char	**handle_map_ended(char **temp_map, char *line, int i)
{
	free_temp_map(temp_map, i);
	free(line);
	return (NULL);
}

static int	get_next_valid_line(int fd, char **line, int *height,
		int *map_ended)
{
	while (1)
	{
		*line = get_next_line(fd);
		if (!*line)
			return (0);
		if (is_empty_line(*line))
		{
			process_empty_map_line(*line, height, map_ended);
			continue ;
		}
		return (1);
	}
}

char	**read_remaining_map_lines(int fd, char **temp_map, int *height,
		int *max_width)
{
	char	*line;
	int		i;
	int		capacity;
	int		map_ended;

	i = *height;
	capacity = 10;
	map_ended = 0;
	while (get_next_valid_line(fd, &line, height, &map_ended))
	{
		if (map_ended)
			return (handle_map_ended(temp_map, line, i));
		if (!handle_line(&temp_map, &capacity, i, line))
			return (NULL);
		if (process_line_content(temp_map, line, i, max_width))
		{
			i++;
			(*height)++;
		}
	}
	return (temp_map);
}
