/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohayek <ohayek@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 15:45:39 by ohayek            #+#    #+#             */
/*   Updated: 2023/10/23 18:04:44 by ohayek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ft_init_cor(t_data *cub3d, double dir_x, double dir_y, char p)
{
	cub3d->player->dir_x = dir_x;
	cub3d->player->dir_y = dir_y;
	if (p == 'N')
	{
		cub3d->player->plane_x = 0.66;
		cub3d->player->plane_y = 0.0;
	}
	else if (p == 'S')
	{
		cub3d->player->plane_x = -0.66;
		cub3d->player->plane_y = 0.0;
	}
	else if (p == 'E')
	{
		cub3d->player->plane_x = 0.0;
		cub3d->player->plane_y = 0.66;
	}
	else if (p == 'W')
	{
		cub3d->player->plane_x = 0.0;
		cub3d->player->plane_y = -0.66;
	}
}

void	ft_init_player(t_data *cub3d)
{
	cub3d->player->pos_x = cub3d->parser->pos_x + 0.1;
	cub3d->player->pos_y = cub3d->parser->pos_y + 0.1;
	if (cub3d->parser->p == 'N')
		ft_init_cor(cub3d, 0.0, -1.0, 'N');
	else if (cub3d->parser->p == 'S')
		ft_init_cor(cub3d, 0.0, 1.0, 'S');
	else if (cub3d->parser->p == 'E')
		ft_init_cor(cub3d, 1.0, 0.0, 'E');
	else if (cub3d->parser->p == 'W')
		ft_init_cor(cub3d, -1.0, 0.0, 'W');
}
