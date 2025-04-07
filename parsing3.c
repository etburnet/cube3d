/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samraoui <samraoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 12:35:00 by doom              #+#    #+#             */
/*   Updated: 2025/04/07 15:53:43 by samraoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include <fcntl.h>

static int	is_valid_any_texture(char *line)
{
	return (is_valid_texture(line, "NO") || is_valid_texture(line, "SO")
		|| is_valid_texture(line, "WE") || is_valid_texture(line, "EA"));
}

static int	handle_line_type(char *line, t_data *data, int fd, int *map_found)
{
	if (is_empty_line(line))
		return (0);
	if (!*map_found && is_valid_any_texture(line))
		return (process_texture_line(line, data, fd));
	else if (!*map_found && is_valid_color_line(line))
		return (process_color_line(data, line, fd));
	else if (!*map_found && check_config_complete(data))
	{
		if (process_map_line(line, data, fd, map_found))
			return (1);
		return (0);
	}
	else if (!*map_found)
		return (handle_other_line(fd));
	return (0);
}

static int	process_file_lines(int fd, t_data *data, int *map_found)
{
	char	*line;
	int		result;

	line = get_next_line(fd);
	while (line)
	{
		result = handle_line_type(line, data, fd, map_found);
		if (result || *map_found == -1)
		{
			free(line);
			line = get_next_line(fd);
			while (line)
			{
				if (line)
					free(line);
				line = get_next_line(fd);
			}
			return (1);
		}
		free(line);
		line = get_next_line(fd);
	}
	return (0);
}

int	ft_parsing(const char *fichier, t_data *data)
{
	int	fd;
	int	map_found;

	map_found = 0;
	fd = open(fichier, O_RDONLY);
	if (fd == -1)
		exit(ft_error("Unable to open file"));
	ft_bzero(data, sizeof(t_data));
	if (process_file_lines(fd, data, &map_found))
	{
		close(fd);
		return (1);
	}
	close(fd);
	verify_parsing_complete(data, map_found);
	return (0);
}

int	ft_cub(const char *str, t_data *data)
{
	int	len;

	len = ft_strlen(str);
	if (len < 4 || ft_strncmp(str + len - 4, ".cub", 4) != 0)
		exit(ft_error("Invalid map file name"));
	if (ft_parsing(str, data) == 1)
		return (1);
	return (0);
}
