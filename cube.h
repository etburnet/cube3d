/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 10:48:14 by eburnet           #+#    #+#             */
/*   Updated: 2025/03/28 14:50:15 by eburnet          ###   ########.fr       */
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
#  define BUFFER_SIZE 1
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
	t_texture	textures[4];
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

int				validate_characters(char *line);
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
void			ft_parsing(const char *str, t_data *data);
void			get_map(int fd, t_data *data, char *first_line);
int				parse_texture(char *line, t_data *data);
int				set_color(t_data *data, const char *line);
int				parse_color(const char *color_str, int *color);
int				assign_texture(char *line, char *path, t_data *data);
int				extract_rgb(const char *color_str, int *values);
int				count_commas(const char *str);
int				validate_component(int component);
int				extract_value(const char **str);
int				is_valid_texture(char *line, char *id);
int				ft_strchr_index(const char *str, char c);
char			*ft_strrjoin(char const *s1, char const *s2);

int				ft_atoi(const char *str);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
void			ft_putstr_fd(char *s, int fd);
int				ft_strlen(const char *str);
char			*ft_substr(char const *s, int start, int len);

#endif