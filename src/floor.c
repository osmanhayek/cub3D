/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohayek <ohayek@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 16:50:00 by ohayek            #+#    #+#             */
/*   Updated: 2023/10/21 21:27:32 by ohayek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ft_search_floor(t_data *cub3d, int y)
{
	int			x;
	t_floor		*f;
	t_player	*p;

	x = 0;
	f = cub3d->floor;
	p = cub3d->player;
	while (x < SCREENWIDTH)
	{
		f->cell_x = (int)(f->floor_x);
		f->cell_y = (int)(f->floor_y);
		f->floor_x += f->floor_step_x;
		f->floor_y += f->floor_step_y;
		my_mlx_put_to_image(cub3d, x, y, cub3d->parser->color_f);
		my_mlx_put_to_image(cub3d, x, SCREENHEIGHT - y - 1, \
		cub3d->parser->color_c);
		x++;
	}
}

void	ft_floor_raycast(t_data *cub3d)
{
	int			y;
	t_floor		*f;
	t_player	*p;

	y = 0;
	f = cub3d->floor;
	p = cub3d->player;
	while (y < SCREENHEIGHT / 2)
	{
		f->ray_dir_x0 = p->dir_x - p->plane_x;
		f->ray_dir_y0 = p->dir_y - p->plane_y;
		f->ray_dir_x1 = p->dir_x + p->plane_x;
		f->ray_dir_y1 = p->dir_y + p->plane_y;
		f->p = y - SCREENHEIGHT / 2;
		f->pos_z = 0.5 * SCREENHEIGHT;
		f->row_distance = f->pos_z / f->p;
		f->floor_step_x = f->row_distance * \
		(f->ray_dir_x1 - f->ray_dir_x0) / SCREENWIDTH;
		f->floor_step_y = f->row_distance * \
		(f->ray_dir_y1 - f->ray_dir_y0) / SCREENWIDTH;
		f->floor_x = p->pos_x + f->row_distance * f->ray_dir_x0;
		f->floor_y = p->pos_y + f->row_distance * f->ray_dir_y0;
		ft_search_floor(cub3d, y);
		y++;
	}
}
