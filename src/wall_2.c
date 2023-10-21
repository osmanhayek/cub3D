/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohayek <ohayek@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 21:18:01 by ohayek            #+#    #+#             */
/*   Updated: 2023/10/21 22:36:18 by ohayek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ft_set_distance(t_player *p, t_wall *w, int side)
{
	if (side == 0)
		w->perp_wall_dist = w->side_dist_x - w->delta_dist_x;
	else
		w->perp_wall_dist = w->side_dist_y - w->delta_dist_y;
}

int	ft_init_hex(t_data *cub3d, int side)
{
	int			res;
	t_wall		*w;

	w = cub3d->wall;
	if (side == 0 && w->ray_dir_x < 0)
		res = 0;
	else if (side == 0 && w->ray_dir_x > 0)
		res = 1;
	else if (side == 1 && w->ray_dir_y < 0)
		res = 2;
	else if (side == 1 && w->ray_dir_y > 0)
		res = 3;
	return (res);
}

void	ft_draw(t_data *cub3d, int x, int tex_num)
{
	int			y;
	u_int32_t	color;

	y = cub3d->wall->draw_start;
	while (y < cub3d->wall->draw_end)
	{
		cub3d->wall->tex_y = (int)cub3d->wall->tex_pos & (64 - 1);
		cub3d->wall->tex_pos += cub3d->wall->step;
		color = cub3d->texture_pixel \
		[tex_num][64 * cub3d->wall->tex_y + cub3d->wall->tex_x];
		my_mlx_put_to_image(cub3d, x, y, color);
		y++;
	}
}
