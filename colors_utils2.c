/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 12:23:41 by doom              #+#    #+#             */
/*   Updated: 2025/04/02 14:29:33 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	skip_spaces(const char **color_str)
{
	while (**color_str && **color_str == ' ')
		(*color_str)++;
	return (1);
}

int	process_digit(const char **color_str, int *values, int *value_index)
{
	values[*value_index] = extract_value(color_str);
	if (!validate_component(values[*value_index]))
		return (0);
	(*value_index)++;
	return (1);
}

int	process_comma(const char **color_str)
{
	(*color_str)++;
	skip_spaces(color_str);
	return (1);
}

int	extract_rgb(const char *color_str, int *values)
{
	int	value_index;

	value_index = 0;
	while (*color_str == ' ')
		color_str++;
	while (*color_str && value_index < 3)
	{
		if (ft_isdigit(*color_str))
		{
			if (!process_rgb_digit(&color_str, values, &value_index))
				return (0);
		}
		else if (*color_str == ',')
		{
			color_str++;
			while (*color_str == ' ')
				color_str++;
		}
		else
			return (0);
	}
	return (value_index == 3);
}

int	parse_color(const char *color_str, int *color)
{
	int	values[3];

	if (count_commas(color_str) != 2)
		return (0);
	if (!extract_rgb(color_str, values))
		return (0);
	color[0] = values[0];
	color[1] = values[1];
	color[2] = values[2];
	return (1);
}
