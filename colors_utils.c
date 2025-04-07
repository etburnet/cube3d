/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 12:23:41 by doom              #+#    #+#             */
/*   Updated: 2025/04/02 14:29:23 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	process_rgb_digit(const char **color_str, int *values, int *value_index)
{
	values[*value_index] = ft_atoi(*color_str);
	if (values[*value_index] < 0 || values[*value_index] > 255)
		return (0);
	(*value_index)++;
	while (ft_isdigit(**color_str))
		(*color_str)++;
	return (1);
}

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	extract_value(const char **str)
{
	int	value;

	value = ft_atoi(*str);
	while (ft_isdigit(**str))
		(*str)++;
	return (value);
}

int	validate_component(int component)
{
	return (component >= 0 && component <= 255);
}

int	count_commas(const char *str)
{
	int	count;

	count = 0;
	while (*str)
	{
		if (*str == ',')
			count++;
		str++;
	}
	return (count);
}
