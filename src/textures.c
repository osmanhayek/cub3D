/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohayek <ohayek@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 21:51:46 by ohayek            #+#    #+#             */
/*   Updated: 2023/10/23 19:40:15 by ohayek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

unsigned int	access_spes_pixel(t_image *image, int tx, int ty)
{
	char			*pixel;
	unsigned int	color;

	pixel = image->image_data + \
	(ty * image->size_line + tx * (image->bits_per_pixel / 8));
	color = *(unsigned int *)pixel;
	return (color);
}

int	ft_check_edge(t_data *cub3d, double x, double y)
{
	if ((int)cub3d->player->pos_x != (int)x)
		if (cub3d->parser->world_map[(int)y][(int)x] == 1)
			return (1);
	return (0);
}
