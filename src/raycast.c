/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohayek <ohayek@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 13:50:43 by ohayek            #+#    #+#             */
/*   Updated: 2023/10/23 18:03:31 by ohayek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ft_raycasting(t_data *cub3d)
{
	ft_fill_image_black(cub3d);
	ft_floor_raycast(cub3d);
	ft_wall_raycast(cub3d);
	mlx_put_image_to_window(cub3d->mlx->mlx_ptr, \
	cub3d->mlx->mlx_window, cub3d->mlx->main_image, 0, 0);
}
