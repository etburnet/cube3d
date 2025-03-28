/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 14:48:11 by doom              #+#    #+#             */
/*   Updated: 2025/03/28 16:29:11 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include <unistd.h>
#include <ctype.h>


int ft_isdigit(int c)
{
    return (c >= '0' && c <= '9');
}

int extract_value(const char **str)
{
    int value = ft_atoi(*str);
    while (ft_isdigit(**str))
        (*str)++;
    return value;
}

int validate_component(int component)
{
    return (component >= 0 && component <= 255);
}

int count_commas(const char *str)
{
    int count = 0;
    while (*str) {
        if (*str == ',')
            count++;
        str++;
    }
    return count;
}

int extract_rgb(const char *color_str, int *values)
{
    int value_index = 0;

    // Skip les espaces au début
    while (*color_str && *color_str == ' ')
        color_str++;

    while (*color_str && value_index < 3)
    {
        if (ft_isdigit(*color_str)) {
            values[value_index] = extract_value(&color_str);
            if (!validate_component(values[value_index]))
                return 0;
            value_index++;
        }
        else if (*color_str == ',') {
            color_str++;
            // Skip les espaces après la virgule
            while (*color_str && *color_str == ' ')
                color_str++;
        }
        else
            return 0;
    }

    return (value_index == 3);
}

int parse_color(const char *color_str, int *color)
{
    int values[3];

    if (count_commas(color_str) != 2 || !extract_rgb(color_str, values)) {
        return 0;
    }

    color[0] = values[0];
    color[1] = values[1];
    color[2] = values[2];

    return 1;
}

int set_color(t_data *data, const char *line) 
{
    int i = 0;
    
    while (line[i] && line[i] == ' ')
        i++;

    if (line[i] == 'F' || line[i] == 'C') 
    {
        if (line[i+1] != ' ')
        {
            ft_error("Format des couleurs incorrect (espace manquant après F/C)");
            return 0;
        }

        int result;
        if (line[i] == 'F') 
        {
            i++;
            while (line[i] && line[i] == ' ')
                i++;
            
            result = parse_color(line + i, data->floor_color);
            if (data->floor_color_set || !result) 
            {
                ft_error("Problème dans l'analyse des couleurs");
                return 0;
            }
            data->floor_color_set = 1;
        }
        else if (line[i] == 'C')
        {
            i++;
            while (line[i] && line[i] == ' ')
                i++;
            
            result = parse_color(line + i, data->ceiling_color);
            if (data->ceiling_color_set || !result)
            {
                ft_error("Problème dans l'analyse des couleurs");
                return 0;
            }
            data->ceiling_color_set = 1;
        }
        return 1;
    }
   	ft_error("Problème dans l'analyse des couleurs");
    return 0;
}
