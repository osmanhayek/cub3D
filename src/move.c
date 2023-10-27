/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohayek <ohayek@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 18:18:09 by ohayek            #+#    #+#             */
/*   Updated: 2023/10/23 18:48:33 by ohayek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	key_press(int keycode, t_data *cub3d)
{
	if (keycode == KEY_W)
		cub3d->keycode[0] = 1;
	if (keycode == KEY_S)
		cub3d->keycode[1] = 1;
	if (keycode == KEY_A)
		cub3d->keycode[2] = 1;
	if (keycode == KEY_D)
		cub3d->keycode[3] = 1;
	if (keycode == KEY_LEFT)
		cub3d->keycode[4] = 1;
	if (keycode == KEY_RIGHT)
		cub3d->keycode[5] = 1;
	if (keycode == 53)
		ft_exit(0, cub3d);
	return (0);
}

int	key_release(int keycode, t_data *cub3d)
{
	if (keycode == KEY_W)
		cub3d->keycode[0] = 0;
	if (keycode == KEY_S)
		cub3d->keycode[1] = 0;
	if (keycode == KEY_A)
		cub3d->keycode[2] = 0;
	if (keycode == KEY_D)
		cub3d->keycode[3] = 0;
	if (keycode == KEY_LEFT)
		cub3d->keycode[4] = 0;
	if (keycode == KEY_RIGHT)
		cub3d->keycode[5] = 0;
	if (keycode == 53)
		ft_exit(0, cub3d);
	return (0);
}

int	calc_move(t_data *cub3d, int sign, double move_speed)
{
	double	x;
	double	y;

	x = cub3d->player->pos_x;
	y = cub3d->player->pos_y;
	if (sign == 1)
	{
		x += cub3d->player->dir_x * move_speed;
		if (ft_check_edge(cub3d, x, y))
			return (1);
		y += cub3d->player->dir_y * move_speed;
	}
	else
	{
		x -= cub3d->player->dir_x * move_speed;
		if (ft_check_edge(cub3d, x, y))
			return (1);
		y -= cub3d->player->dir_y * move_speed;
	}
	if (cub3d->parser->world_map[(int)y][(int)x] == 1)
		return (1);
	cub3d->player->pos_x = x;
	cub3d->player->pos_y = y;
	return (0);
}

void	calc_rot(t_data *cub3d, double rot_speed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = cub3d->player->dir_x;
	old_plane_x = cub3d->player->plane_x;
	cub3d->player->dir_x = cub3d->player->dir_x * cos(rot_speed)
		- cub3d->player->dir_y * sin(rot_speed);
	cub3d->player->dir_y = old_dir_x * sin(rot_speed) + cub3d->player->dir_y
		* cos(rot_speed);
	cub3d->player->plane_x = cub3d->player->plane_x * cos(rot_speed)
		- cub3d->player->plane_y * sin(rot_speed);
	cub3d->player->plane_y = old_plane_x * sin(rot_speed)
		+ cub3d->player->plane_y * cos(rot_speed);
}

int	calc_move_d(t_data *cub3d, int sign, double move_speed)
{
	double	x;
	double	y;

	x = cub3d->player->pos_x;
	y = cub3d->player->pos_y;
	if (sign == 1)
	{
		x = cub3d->player->pos_x + cub3d->player->plane_x * move_speed;
		if (ft_check_edge(cub3d, x, y))
			return (1);
		y = cub3d->player->pos_y + cub3d->player->plane_y * move_speed;
	}
	else
	{
		x = cub3d->player->pos_x - cub3d->player->plane_x * move_speed;
		if (ft_check_edge(cub3d, x, y))
			return (1);
		y = cub3d->player->pos_y - cub3d->player->plane_y * move_speed;
	}
	if (cub3d->parser->world_map[(int)y][(int)x] == 1)
		return (1);
	cub3d->player->pos_x = x;
	cub3d->player->pos_y = y;
	return (0);
}
