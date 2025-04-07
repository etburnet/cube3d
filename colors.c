/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 14:48:11 by doom              #+#    #+#             */
/*   Updated: 2025/04/02 14:29:33 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include <unistd.h>

int	process_floor_color(t_data *data, const char *line, int i)
{
	int	result;

	i++;
	while (line[i] && line[i] == ' ')
		i++;
	result = parse_color(line + i, data->floor_color);
	if (data->floor_color_set || !result)
	{
		ft_error("Problème dans l'analyse des couleurs");
		return (0);
	}
	data->floor_color_set = 1;
	return (1);
}

int	process_ceiling_color(t_data *data, const char *line, int i)
{
	int	result;

	i++;
	while (line[i] && line[i] == ' ')
		i++;
	result = parse_color(line + i, data->ceiling_color);
	if (data->ceiling_color_set || !result)
	{
		ft_error("Problème dans l'analyse des couleurs");
		return (0);
	}
	data->ceiling_color_set = 1;
	return (1);
}

int	check_color_format(const char *line, int i)
{
	if (line[i + 1] != ' ')
	{
		ft_error("Format des couleurs incorrect (espace manquant après F/C)");
		return (0);
	}
	return (1);
}

int	process_color_type(t_data *data, const char *line, int i)
{
	if (!check_color_format(line, i))
		return (0);
	if (line[i] == 'F')
		return (process_floor_color(data, line, i));
	else if (line[i] == 'C')
		return (process_ceiling_color(data, line, i));
	return (0);
}

int	set_color(t_data *data, const char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	if (line[i] == 'F' || line[i] == 'C')
		return (process_color_type(data, line, i));
	ft_error("Problème dans l'analyse des couleurs");
	return (0);
}
