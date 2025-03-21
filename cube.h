/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 10:48:14 by eburnet           #+#    #+#             */
/*   Updated: 2025/03/21 14:27:16 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H
# include "./libft/libft.h"
# include <math.h>
# include <mlx.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_texture
{
	uint32_t	*pixels;
	int			bpp;
	int			line_length;
	int			endian;
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
	void		*no_texture;
	void		*so_texture;
	void		*we_texture;
	void		*ea_texture;
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

}				t_data;

int				ft_raycast(t_data *data);
void			ft_dist_draw_points(t_data *d, int x);
void			ft_draw(t_data *d, int line_height, int x);
void			ft_put_buff(t_data *d, int line_height, int x, int tex_x);
void			ft_find_wall(t_data *d);
void			ft_init_raycast(t_data *d, int x);
void			ft_init_side_dist(t_data *d);
void			free_map(int **tab, int len);
int				ft_x_close(t_data *data);
int				ft_error(char *str);
#endif