/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samraoui <samraoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 14:13:48 by doom              #+#    #+#             */
/*   Updated: 2025/04/07 15:03:57 by samraoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static int	check_path_validity(char *path)
{
	int	fd;
	int	len;

	if (!path)
		return (ft_error("Memory allocation failed"), 0);
	if (!*path)
	{
		free(path);
		return (ft_error("Missing texture path"), 0);
	}
	len = ft_strlen(path);
	if (len < 4 || ft_strncmp(path + len - 4, ".xpm", 4) != 0)
	{
		free(path);
		return (ft_error("Texture file must be .xpm format"), 0);
	}
	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		free(path);
		return (ft_error("opening texture file"), 0);
	}
	close(fd);
	return (1);
}

static char	*extract_path(char *line)
{
	int		i;
	char	*path;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	i += 2;
	while (line[i] && line[i] == ' ')
		i++;
	path = ft_strtrim(line + i, " \t\n\r");
	return (path);
}

static char	*get_texture_path(char *line)
{
	char	*path;

	path = extract_path(line);
	if (!check_path_validity(path))
		return (NULL);
	return (path);
}

int	assign_texture(char *line, char *path, t_data *data)
{
	if (is_valid_texture(line, "NO") && !data->texs[0].tex)
		data->texs[0].tex = path;
	else if (is_valid_texture(line, "SO") && !data->texs[1].tex)
		data->texs[1].tex = path;
	else if (is_valid_texture(line, "WE") && !data->texs[3].tex)
		data->texs[3].tex = path;
	else if (is_valid_texture(line, "EA") && !data->texs[2].tex)
		data->texs[2].tex = path;
	else
	{
		free(path);
		return (ft_error("Invalid or duplicate texture identifier"), 0);
	}
	return (free(path), 1);
}

int	parse_texture(char *line, t_data *data)
{
	char	*path;

	if (!(is_valid_texture(line, "NO") || is_valid_texture(line, "SO")
			|| is_valid_texture(line, "WE") || is_valid_texture(line, "EA")))
		return (ft_error("Invalid texture format"), 0);
	path = get_texture_path(line);
	if (!path)
		return (0);
	return (assign_texture(line, path, data));
}
