/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samraoui <samraoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 17:10:29 by doom              #+#    #+#             */
/*   Updated: 2025/04/07 15:05:54 by samraoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	ft_strchr_index(const char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int	is_map_closed(t_data *data)
{
	int	valid;
	int	max_content_width;

	valid = 1;
	max_content_width = 0;
	max_content_width = get_max_content_width(data);
	valid = check_map_boundaries(data, max_content_width);
	if (valid)
		convert_spaces_to_walls(data);
	return (valid);
}
