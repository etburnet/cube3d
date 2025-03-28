/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 13:41:00 by doom              #+#    #+#             */
/*   Updated: 2025/03/28 14:54:43 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include <fcntl.h>

void	ft_bzero(void *b, size_t n)
{
	unsigned char	*ptr;

	ptr = (unsigned char*)b;
	while (n-- > 0)
		*(ptr++) = 0;
}

void	ft_parsing(const char *fichier, t_data *data)
{
    int		fd;
    char	*line;
    int     map_found;

    map_found = 0;
    if ((fd = open(fichier, O_RDONLY)) == -1)
        exit(ft_error("Unable to open file"));
    ft_bzero(data, sizeof(t_data));
    line = NULL;
    while ((line = get_next_line(fd)))
    {
        if ((line[0] == '\n' || line[0] == '\0' || (line[0] == ' ' && line[1] == '\n')))
        {
            free(line);
            continue;
        }
        if (!map_found && (is_valid_texture(line, "NO") || is_valid_texture(line, "SO") ||
            is_valid_texture(line, "WE") || is_valid_texture(line, "EA")))
        {
            if (!parse_texture(line, data))
            {
                free(line);
                close(fd);
                exit(EXIT_FAILURE);
            }
        }
        else if (!map_found && (line[0] == 'F' || line[0] == 'C' || 
			(line[0] == ' ' && 
			 ((ft_strchr_index(line, 'F') >= 0 && line[ft_strchr_index(line, 'F')] == 'F') || 
			  (ft_strchr_index(line, 'C') >= 0 && line[ft_strchr_index(line, 'C')] == 'C'))))) 
        {
            if (!set_color(data, line))
            {
                free(line);
                close(fd);
                exit(EXIT_FAILURE);
            }
        }
        else if (!map_found && data->textures[0].tex && data->textures[1].tex && 
                data->textures[2].tex && data->textures[3].tex && 
                data->floor_color_set && data->ceiling_color_set)
        {
            if (validate_characters(line))
            {
                map_found = 1;
                get_map(fd, data, line);
                free(line);
                break;
            }
            else
            {
                free(line);
                close(fd);
                exit(ft_error("Invalid map line format"));
            }
        }
        else if (!map_found)
        {
            free(line);
            close(fd);
            exit(ft_error("Invalid configuration format"));
        }
        free(line);
    }
    close(fd);
    if (!data->textures[0].tex || !data->textures[1].tex || !data->textures[2].tex || !data->textures[3].tex)
        exit(ft_error("Missing texture(s)"));
    if (!data->floor_color_set || !data->ceiling_color_set)
        exit(ft_error("Missing floor or ceiling color"));
    if (!map_found)
        exit(ft_error("No map found in file"));
}

int	ft_cub(const char *str, t_data *data)
{
    int	len;

    len = ft_strlen(str);
    if (len < 4 || ft_strncmp(str + len - 4, ".cub", 4) != 0)
        exit(ft_error("Invalid map file name"));
    ft_parsing(str, data);
    return (0);
}

// #include "cube.h"
// #include <stdio.h>
// #include <stdlib.h>

// void	print_parsed_data(t_data *data)
// {
//     // Afficher les textures
//     printf("NO Texture: %s\n", data->no_texture ? data->no_texture : "Not set");
//     printf("SO Texture: %s\n", data->so_texture ? data->so_texture : "Not set");
//     printf("WE Texture: %s\n", data->we_texture ? data->we_texture : "Not set");
//     printf("EA Texture: %s\n", data->ea_texture ? data->ea_texture : "Not set");

//     // Afficher les couleurs
//     printf("Floor Color: %d, %d, %d\n", data->floor_color[0], data->floor_color[1], data->floor_color[2]);
//     printf("Ceiling Color: %d, %d, %d\n", data->ceiling_color[0], data->ceiling_color[1], data->ceiling_color[2]);

//     // Afficher la carte
//     printf("Map:\n");
//     for (int i = 0; i < data->map_height; i++)
//     {
//         for (int j = 0; j < data->map_width; j++)
//             printf("%d ", data->map[i][j]);
//         printf("\n");
//     }
// }

// int	main(int argc, char **argv)
// {
//     t_data	data;

//     if (argc != 2)
//     {
//         ft_putstr_fd("Usage: ./cub3D <map_file>\n", 2);
//         return (1);
//     }
//     ft_cub(argv[1], &data);
//     print_parsed_data(&data);
//     for (int i = 0; i < data.map_height; i++)
//         free(data.map[i]);
//     free(data.map);
//     free(data.no_texture);
//     free(data.so_texture);
//     free(data.we_texture);
//     free(data.ea_texture);
//     return (0);
// }