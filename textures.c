/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 14:13:48 by doom              #+#    #+#             */
/*   Updated: 2025/03/28 14:38:30 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int is_valid_texture(char *line, char *id)
{
    int i;
    int j;

    i = 0;
    while (line[i] && line[i] == ' ')
        i++;
    
    j = 0;
    while (id[j])
    {
        if (line[i] != id[j])
            return (0);
        i++;
        j++;
    }
    return (line[i] == ' ');
}

static char *get_texture_path(char *line)
{
    char *path;
    int  fd;
    int  i = 0;
    
    while (line[i] && line[i] == ' ')
        i++;
    i += 2;
    while (line[i] && line[i] == ' ')
        i++;
    
    path = ft_strtrim(line + i, " \t\n\r");
    if (!path)
        return (ft_error("Memory allocation failed"), NULL);
    if (!*path)
    {
        free(path);
        return (ft_error("Missing texture path"), NULL);
    }
    int len = ft_strlen(path);
    if (len < 4 || ft_strncmp(path + len - 4, ".xpm", 4) != 0)
    {
        free(path);
        return (ft_error("Texture file must be .xpm format"), NULL);
    }
    fd = open(path, O_RDONLY);
    if (fd == -1)
    {
        free(path);
        return (ft_error("opening texture file"), NULL);
    }
    close(fd);
    return (path);
}

int assign_texture(char *line, char *path, t_data *data)
{
    if (is_valid_texture(line, "NO") && !data->textures[0].tex)
        data->textures[0].tex = path;
    else if (is_valid_texture(line, "SO") && !data->textures[1].tex)
        data->textures[1].tex = path;
    else if (is_valid_texture(line, "WE") && !data->textures[3].tex)
        data->textures[3].tex = path;
    else if (is_valid_texture(line, "EA") && !data->textures[2].tex)
        data->textures[2].tex = path;
    else
    {
        free(path);
        return (ft_error("Invalid or duplicate texture identifier"), 0);
    }
    return (1);
}

int parse_texture(char *line, t_data *data)
{
    char *path;

    if (!(is_valid_texture(line, "NO") || is_valid_texture(line, "SO") ||
          is_valid_texture(line, "WE") || is_valid_texture(line, "EA")))
        return (ft_error("Invalid texture format"), 0);
    path = get_texture_path(line);
    if (!path)
        return (0);
    return (assign_texture(line, path, data));
}

// #include <stdio.h>
// #include <stdlib.h>

// void print_texture_paths(t_data *data)
// {
//     printf("NO Texture: %s\n", data->no_texture ? data->no_texture : "Not set");
//     printf("SO Texture: %s\n", data->so_texture ? data->so_texture : "Not set");
//     printf("WE Texture: %s\n", data->we_texture ? data->we_texture : "Not set");
//     printf("EA Texture: %s\n", data->ea_texture ? data->ea_texture : "Not set");
// }

// int main(void)
// {
//     t_data data = {0}; // Initialiser la structure à 0
//     char *test_lines[] = {
//         "NO ./textures/north.xpm",
//         "SO ./textures/south.xpm",
//         "WE ./textures/west.xpm",
//         "EA ./textures/east.xpm",
//         "NO ./textures/duplicate.xpm", // Test duplication
//         "INVALID ./textures/invalid.xpm", // Test identifiant invalide
//         NULL
//     };

//     for (int i = 0; test_lines[i]; i++)
//     {
//         printf("Parsing line: %s\n", test_lines[i]);
//         parse_texture(test_lines[i], &data);
//     }

//     printf("\nFinal texture paths:\n");
//     print_texture_paths(&data);

//     // Libérer la mémoire allouée pour les textures
//     free(data.no_texture);
//     free(data.so_texture);
//     free(data.we_texture);
//     free(data.ea_texture);

//     return 0;
// }