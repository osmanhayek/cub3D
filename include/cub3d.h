/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohayek <ohayek@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 13:26:20 by ohayek            #+#    #+#             */
/*   Updated: 2023/10/21 23:34:40 by ohayek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../minilibx/mlx.h"
# include "../get_next_line/get_next_line.h"
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <math.h>

# define SCREENWIDTH 1080
# define SCREENHEIGHT 1280
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_ESC 53

typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*mlx_window;
	void	*main_image;
	char	*image_data;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
}	t_mlx;

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

typedef struct s_floor
{
	double	ray_dir_x0;
	double	ray_dir_y0;
	double	ray_dir_x1;
	double	ray_dir_y1;
	int		p;
	int		cell_x;
	int		cell_y;
	int		tx;
	int		ty;
	float	pos_z;
	float	row_distance;
	float	floor_step_x;
	float	floor_step_y;
	float	floor_x;
	float	floor_y;
}	t_floor;

typedef struct s_wall
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	double	wall_x;
	double	step;
	double	tex_pos;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		tex_x;
	int		tex_y;
}	t_wall;

typedef struct s_image
{
	void	*image;
	char	*image_data;
	int		bits_per_pixel;
	int		size_line;
}	t_image;

typedef struct s_parser
{
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	char		**all_line;
	char		p;
	double		pos_x;
	double		pos_y;
	int			map_begin;
	int			**world_map;
	int			line_max;
	int			column_max;
	t_image		*textures;
	u_int32_t	color_c;
	u_int32_t	color_f;
}	t_parser;

typedef struct s_data
{
	t_parser	*parser;
	t_player	*player;
	t_wall		*wall;
	t_floor		*floor;
	t_mlx		*mlx;
	u_int32_t	texture_pixel[4][64 * 64];
	int			keycode[7];
}	t_data;

void	ft_raycasting(t_data *cub3d);
void	ft_init_mlx(t_data *cub3d);
void	ft_init_player(t_data *cub3d);
void	ft_floor_raycast(t_data *cub3d);
void	ft_wall_raycast(t_data *cub3d);
void	my_mlx_put_to_image(t_data *cub3d, int x, int y, u_int32_t color);
void	ft_set_distance(t_player *p, t_wall *w, int side);
void	ft_draw(t_data *cub3d, int x, int tex_num);
int		ft_init_hex(t_data *cub3d, int side);
unsigned int	access_spes_pixel(t_image *image, int tx, int ty);

#endif
