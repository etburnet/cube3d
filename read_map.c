/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 15:50:50 by doom              #+#    #+#             */
/*   Updated: 2025/03/28 16:10:07 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include <stdlib.h>
#include <unistd.h>

int	get_map_width(char *line)
{
    int	width;
    int i;
    
    i = 0;
    width = 0;
    while (line[i] && line[i] != '\n')
    {
        width++;
        i++;
    }
    return (width);
}

int	convert_char_to_int(char c, t_data *data, int x, int y)
{
    if (c == '0')
        return (0);
    if (c == '1')
        return (1);
    if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
    {
        if (data->pos_depart != '\0')
        	exit (ft_error("Error: Multiple player spawn points\n"));
        data->pos_depart = c;
        data->pos_x = x + 0.5;
        data->pos_y = y + 0.5;
        return (0);
    }
    if (c == ' ')
        return (-3);
    if (c == '\n')
        return (-2);
    return (-1);
}

int	*convert_line_to_int(char *line, int width, t_data *data, int y)
{
    int	*row;
    int	i;

    row = malloc(sizeof(int) * width);
    if (!row)
        return (NULL);
    i = 0;
    while (i < width && line[i] && line[i] != '\n')
    {
        row[i] = convert_char_to_int(line[i], data, i, y);
        if (row[i] == -1)
        {
            printf("Error: Invalid character '%c' at (%d, %d)\n", line[i], y, i);
            free(row);
            return (NULL);
        }
        i++;
    }
    while (i < width)
    {
        row[i] = 1;
        i++;
    }
    
    return (row);
}

void	print_map(t_data *data)
{
    for (int i = 0; i < data->map_height; i++)
    {
        for (int j = 0; j < data->map_width; j++)
            printf("%2d ", data->map[i][j]);
        printf("\n");
    }
}

void get_map(int fd, t_data *data, char *first_line)
{
    char    *line;
    int     i;
    int     map_ended;

    map_ended = 0;
    data->map_height = 0;
    data->map_width = 0;
    data->map = NULL;
    data->pos_depart = '\0';
    i = 0;
    if (first_line)
    {
        line = strdup(first_line);
        if (!line)
            exit(EXIT_FAILURE);
        data->map_width = get_map_width(line);
        data->map = malloc(sizeof(int *));
        if (!data->map)
        {
            free(line);
            exit(EXIT_FAILURE);
        }
        data->map[0] = convert_line_to_int(line, data->map_width, data, 0);
        if (!data->map[0])
        {
            free(line);
            free(data->map);
            exit(EXIT_FAILURE);
        }

        free(line);
        i++;
    }
    while ((line = get_next_line(fd)))
    {
        if (map_ended && line[0] != '\n' && line[0] != '\0')
        {
            free(line);
            exit(ft_error("Error: Map must be the last element in the file and properly enclosed\n"));
        }

        if (line[0] == '\n' || line[0] == '\0') // Ligne vide
        {
            if (i > 0)
                map_ended = 1;
            free(line);
            continue;
        }
        if (!validate_characters(line))
        {
            free(line);
            exit(ft_error("Error: Invalid character in map\n"));
        }

        int **new_map;
        new_map = realloc(data->map, sizeof(int *) * (i + 1));
        if (!new_map)
        {
            free(data->map);
            free(line);
            exit(EXIT_FAILURE);
        }
        data->map = new_map;

        data->map[i] = convert_line_to_int(line, data->map_width, data, i);
        if (!data->map[i])
        {
            free(line);
            exit(ft_error("Error: Invalid character in map\n"));
        }

        free(line);
        i++;
    }
    data->map_height = i;
    close(fd);

    if (data->pos_depart == '\0')
        exit(ft_error("Error: No player spawn point\n"));

    if (!is_map_closed(data))
    {
        exit(ft_error("Error: Map is not closed by walls\n"));
    }

    fill_short_lines(data);
}



// #include <fcntl.h>
// #include <stdio.h>

// int	main(int argc, char **argv)
// {
//     t_data	data;
//     int		fd;

//     if (argc != 2)
//     {
//         write(2, "Usage: ./cub3D <map_file>\n", 26);
//         return (1);
//     }

//     fd = open(argv[1], O_RDONLY);
//     if (fd == -1)
//     {
//         perror("Error opening file");
//         return (1);
//     }

//     get_map(fd, &data);

//     // Affichage de la carte pour vérification
//     for (int i = 0; i < data.map_height; i++)
//     {
//         for (int j = 0; j < data.map_width; j++)
//             printf("%d ", data.map[i][j]);
//         printf("\n");
//     }

//     // Libération de la mémoire
//     for (int i = 0; i < data.map_height; i++)
//         free(data.map[i]);
//     free(data.map);

//     return (0);
// }