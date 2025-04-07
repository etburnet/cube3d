/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samraoui <samraoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 13:41:00 by doom              #+#    #+#             */
/*   Updated: 2025/04/07 15:02:20 by samraoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include <fcntl.h>

void	ft_bzero(void *b, size_t n)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)b;
	while (n-- > 0)
		*(ptr++) = 0;
}

int	process_texture_line(char *line, t_data *data, int fd)
{
	if (!parse_texture(line, data))
	{
		close(fd);
		return (1);
	}
	return (0);
}

int	process_color_line(t_data *data, char *line, int fd)
{
	if (!set_color(data, line))
	{
		close(fd);
		return (1);
	}
	return (0);
}

int	is_valid_color_line(char *line)
{
	if (line[0] == 'F' || line[0] == 'C')
		return (1);
	if (line[0] == ' ')
	{
		if (ft_strchr_index(line, 'F') >= 0 && line[ft_strchr_index(line,
					'F')] == 'F')
			return (1);
		if (ft_strchr_index(line, 'C') >= 0 && line[ft_strchr_index(line,
					'C')] == 'C')
			return (1);
	}
	return (0);
}

int	is_empty_line(char *line)
{
	if (line[0] == '\n' || line[0] == '\0')
		return (1);
	if (line[0] == ' ' && line[1] == '\n')
		return (1);
	return (0);
}
