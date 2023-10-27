/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohayek <ohayek@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 16:47:47 by ohayek            #+#    #+#             */
/*   Updated: 2023/10/24 16:18:33 by ohayek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ft_init_dda(t_player *p, t_wall *w)
{
	if (w->ray_dir_x < 0)
	{
		w->step_x = -1;
		w->side_dist_x = (p->pos_x - w->map_x) * w->delta_dist_x;
	}
	else
	{
		w->step_x = 1;
		w->side_dist_x = (w->map_x + 1.0 - p->pos_x) * w->delta_dist_x;
	}
	if (w->ray_dir_y < 0)
	{
		w->step_y = -1;
		w->side_dist_y = (p->pos_y - w->map_y) * w->delta_dist_y;
	}
	else
	{
		w->step_y = 1;
		w->side_dist_y = (w->map_y + 1.0 - p->pos_y) * w->delta_dist_y;
	}
}

void	ft_apply_dda(t_data *cub3d, int *side)
{
	int			hit;
	t_player	*p;
	t_wall		*w;

	hit = 0;
	p = cub3d->player;
	w = cub3d->wall;
	while (hit == 0)
	{
		if (w->side_dist_x < w->side_dist_y)
		{
			w->side_dist_x += w->delta_dist_x;
			w->map_x += w->step_x;
			*side = 0;
		}
		else
		{
			w->side_dist_y += w->delta_dist_y;
			w->map_y += w->step_y;
			*side = 1;
		}
		if (cub3d->parser->world_map[w->map_y][w->map_x] == 1)
			hit = 1;
	}
	ft_set_distance(w, *side);
}

void	ft_set_cor(t_wall *w, int side)
{
	w->tex_x = (int)(w->wall_x * 64.0);
	if (side == 0 && w->ray_dir_x < 0)
		w->tex_x = 64 - w->tex_x - 1;
	if (side == 1 && w->ray_dir_y > 0)
		w->tex_x = 64 - w->tex_x - 1;
	w->step = 64.0 / w->line_height;
	w->tex_pos = (w->draw_start - SCREENHEIGHT / 2 + w->line_height / 2) \
	* w->step;
}

void	ft_draw_wall(t_data *cub3d, int side, int x)
{
	t_wall		*w;
	t_player	*p;
	int			tex_num;

	w = cub3d->wall;
	p = cub3d->player;
	w->line_height = (int)(1 * SCREENHEIGHT / w->perp_wall_dist);
	w->draw_start = -w->line_height / 2 + SCREENHEIGHT / 2;
	if (w->draw_start < 0)
		w->draw_start = 0;
	w->draw_end = w->line_height / 2 + SCREENHEIGHT / 2;
	if (w->draw_end >= SCREENHEIGHT)
		w->draw_end = SCREENHEIGHT - 1;
	tex_num = ft_init_hex(cub3d, side);
	if (side == 0)
		w->wall_x = p->pos_y + w->perp_wall_dist * w->ray_dir_y;
	else
		w->wall_x = p->pos_x + w->perp_wall_dist * w->ray_dir_x;
	w->wall_x -= floor(w->wall_x);
	ft_set_cor(w, side);
	ft_draw(cub3d, x, tex_num);
}

void	ft_wall_raycast(t_data *cub3d)
{
	int			x;
	int			side;
	t_wall		*w;
	t_player	*p;

	x = 0;
	w = cub3d->wall;
	p = cub3d->player;
	while (x < SCREENWIDTH)
	{
		w->camera_x = 2 * x / (double)SCREENWIDTH - 1;
		w->ray_dir_x = p->dir_x + p->plane_x * w->camera_x;
		w->ray_dir_y = p->dir_y + p->plane_y * w->camera_x;
		w->map_x = (int)p->pos_x;
		w->map_y = (int)p->pos_y;
		w->delta_dist_x = fabs(1.0 / w->ray_dir_x);
		w->delta_dist_y = fabs(1.0 / w->ray_dir_y);
		ft_init_dda(p, w);
		ft_apply_dda(cub3d, &side);
		ft_draw_wall(cub3d, side, x);
		x++;
	}
}
