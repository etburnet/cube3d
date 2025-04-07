/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samraoui <samraoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 11:55:29 by samraoui          #+#    #+#             */
/*   Updated: 2025/04/07 15:28:08 by samraoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	process_first_map_line(char **temp_map, char *first_line, int *i,
		int *max_width)
{
	if (first_line && *first_line)
	{
		temp_map[*i] = ft_strdup(first_line);
		if (!temp_map[*i])
			return (0);
		*max_width = get_map_width(first_line);
		(*i)++;
		return (1);
	}
	return (0);
}

int	process_empty_map_line(char *line, int *height, int *map_ended)
{
	if (*height > 0)
		*map_ended = 1;
	free(line);
	return (1);
}

int	process_map_ended(char **temp_map, char *line, int i)
{
	free_temp_map(temp_map, i);
	free(line);
	return (0);
}

int	add_line_to_map(char **temp_map, char *line, int i, int *max_width)
{
	int	width;

	temp_map[i] = line;
	width = get_map_width(line);
	if (width > *max_width)
		*max_width = width;
	return (1);
}

char	**read_all_map_lines(int fd, char *first_line, int *height,
		int *max_width)
{
	char	**temp_map;
	int		capacity;
	int		i;

	capacity = 10;
	temp_map = malloc(sizeof(char *) * capacity);
	if (!temp_map)
		return (NULL);
	i = 0;
	*height = 0;
	*max_width = 0;
	if (process_first_map_line(temp_map, first_line, &i, max_width))
		(*height)++;
	return (read_remaining_map_lines(fd, temp_map, height, max_width));
}
