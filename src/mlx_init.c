/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohayek <ohayek@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 16:07:10 by ohayek            #+#    #+#             */
/*   Updated: 2023/10/21 21:43:14 by ohayek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	my_mlx_put_to_image(t_data *cub3d, int x, int y, u_int32_t color)
{
	char	*pixel;

	pixel = cub3d->mlx->image_data + \
	(y * cub3d->mlx->size_line + x * (cub3d->mlx->bits_per_pixel / 8));
	*(unsigned int *)pixel = color;
}

void	ft_init_mlx(t_data *cub3d)
{
	cub3d->mlx->mlx_ptr = mlx_init();
	cub3d->mlx->mlx_window = mlx_new_window(cub3d->mlx->mlx_ptr, \
	SCREENWIDTH, SCREENHEIGHT, "CUB3D");
	cub3d->mlx->main_image = mlx_new_image(cub3d->mlx->mlx_ptr, \
	SCREENWIDTH, SCREENHEIGHT);
	cub3d->mlx->image_data = mlx_get_data_addr(cub3d->mlx->main_image, \
	&cub3d->mlx->bits_per_pixel, &cub3d->mlx->size_line, &cub3d->mlx->endian);
}
