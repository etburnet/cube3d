/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samraoui <samraoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 10:48:14 by eburnet           #+#    #+#             */
/*   Updated: 2025/04/07 16:09:00 by samraoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H
# include <ctype.h>
# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4000000
# endif

typedef struct s_texture
{
	uint32_t	*pixels;
	int			bpp;
	int			line_length;
	int			endian;
	void		*tex;
}				t_texture;

typedef struct s_mooves
{
	int			w;
	int			s;
	int			a;
	int			d;
	int			l_arrow;
	int			r_arrow;
}				t_mooves;

typedef struct s_data
{
	int			**map;
	int			map_width;
	int			map_height;
	int			floor_color[3];
	int			ceiling_color[3];
	int			tex_width;
	int			tex_height;
	t_texture	texs[4];
	t_mooves	keys;

	void		*mlx;
	void		*mlx_win;
	int			screen_width;
	int			screen_height;

	void		*img;
	uint32_t	*addr;
	int			bpp;
	int			line_length;
	int			endian;

	char		pos_depart;
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;

	double		cam_x;
	double		ray_dir_x;
	double		ray_dir_y;
	double		side_dist_x;
	double		side_dist_y;
	double		delta_dist_x;
	double		delta_dist_y;
	int			map_x;
	int			map_y;
	double		perp_wall_dist;
	int			step_x;
	int			step_y;
	int			hit;
	int			side;

	int			draw_start;
	int			draw_end;

	int			floor_color_set;
	int			ceiling_color_set;

}				t_data;

int				ft_raycast(t_data *data);
void			ft_dist_draw_points(t_data *d, int x);
void			ft_wall(t_data *d, int line_height, int x);
void			ft_put_buff(t_data *d, int line_height, int x, int tex_x);
void			ft_find_wall(t_data *d);
void			ft_init_raycast(t_data *d, int x);
void			ft_init_side_dist(t_data *d);
void			free_map(int **tab, int len);
int				ft_x_close(t_data *data);
int				ft_error(char *str);
int				ft_textures(t_data *d);
unsigned long	create_rgb(int r, int g, int b);
void			ft_rotate(t_data *d);
void			ft_av_ar(t_data *d);
void			ft_ga_dr(t_data *d);
int				ft_key_release(int keycode, t_data *d);
int				ft_key_press(int keycode, t_data *d);
void			fill_short_lines(t_data *data);
int				is_map_closed(t_data *data);
char			*get_next_line(int fd);
char			*get_next_line(int fd);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strchr(const char *str, int c);
char			*ft_strtrim(char const *s1, char const *set);
char			*ft_strdup(const char *s);
int				ft_atoi(const char *str);
int				ft_isdigit(int c);
int				ft_cub(const char *str, t_data *data);
int				ft_parsing(const char *str, t_data *data);
int				get_map(int fd, t_data *data, char *first_line);
int				parse_texture(char *line, t_data *data);
int				set_color(t_data *data, const char *line);
int				parse_color(const char *color_str, int *color);
int				assign_texture(char *line, char *path, t_data *data);
int				extract_rgb(const char *color_str, int *values);
int				count_commas(const char *str);
int				validate_component(int component);
int				extract_value(const char **str);
int				process_rgb_digit(const char **color_str, int *values,
					int *value_index);
int				is_valid_texture(char *line, char *id);
int				ft_strchr_index(const char *str, char c);
char			*ft_strrjoin(char const *s1, char const *s2);
void			ft_bzero(void *b, size_t n);
int				process_texture_line(char *line, t_data *data, int fd);
int				process_color_line(t_data *data, char *line, int fd);
int				is_valid_color_line(char *line);
int				is_empty_line(char *line);
int				process_map_line(char *line, t_data *data, int fd,
					int *map_found);
int				handle_other_line(int fd);
int				check_textures_loaded(t_data *data);
int				check_colors_loaded(t_data *data);
int				check_config_complete(t_data *data);
void			verify_parsing_complete(t_data *data, int map_found);
int				ft_strlen(const char *str);
char			*ft_substr(char const *s, int start, int len);
void			ft_putstr_fd(char *s, int fd);
int				get_map_width(char *line);
void			set_player_position(t_data *data, char c, int x, int y);
int				convert_char_to_int(char c, t_data *data, int x, int y);
int				*convert_line_to_int(char *line, int width, t_data *data,
					int y);
int				process_first_line(t_data *data, char *first_line, int *i);
int				handle_empty_line(char *line, int i, int *map_ended);
int				allocate_new_map_row(t_data *data, int i);
void			ft_exit_on_invalid_map(t_data *data, char *error_message);
char			**read_all_map_lines(int fd, char *first_line, int *height,
					int *max_width);
void			free_temp_map(char **temp_map, int height);
int				resize_temp_map(char ***temp_map, int *capacity,
					int current_size);
int				get_map_width(char *line);
int				is_empty_line(char *line);
void			convert_spaces_to_walls(t_data *data);
void			print_map_debug(t_data *data);
int				get_max_content_width(t_data *data);
int				check_boundary_condition(t_data *data, int i, int j,
					int max_width);
int				check_adjacent_spaces(t_data *data, int i, int j,
					int max_width);
int				check_map_boundaries(t_data *data, int max_content_width);
int				should_convert_to_wall(t_data *data, int i, int j);
void			convert_spaces_to_walls(t_data *data);
void			fill_short_lines(t_data *data);
int				validate_characters(char *line);
int				process_first_map_line(char **temp_map, char *first_line,
					int *i, int *max_width);
int				process_empty_map_line(char *line, int *height, int *map_ended);
int				process_map_ended(char **temp_map, char *line, int i);
int				add_line_to_map(char **temp_map, char *line, int i,
					int *max_width);
char			**read_remaining_map_lines(int fd, char **temp_map, int *height,
					int *max_width);
void			free_temp_map(char **temp_map, int height);
int				resize_temp_map(char ***temp_map, int *capacity,
					int current_size);
void			verify_parsing_complete(t_data *data, int map_found);
int				resize_temp_map(char ***temp_map, int *capacity, int current_size);
void			free_temp_map(char **temp_map, int height);
int				handle_map_capacity(char ***temp_map, int *capacity, int i);

#endif