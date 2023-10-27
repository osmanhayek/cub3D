/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohayek <ohayek@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 16:07:10 by ohayek            #+#    #+#             */
/*   Updated: 2023/10/24 16:19:28 by ohayek           ###   ########.fr       */
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

void	ft_fill_image_black(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < SCREENHEIGHT)
	{
		while (j < SCREENWIDTH)
			my_mlx_put_to_image(data, j++, i, 0x0);
		i++;
	}
}

int	ft_exit(int s, t_data *x)
{
	mlx_destroy_image(x->mlx->mlx_ptr, x->mlx->main_image);
	mlx_destroy_window(x->mlx->mlx_ptr, x->mlx->mlx_window);
	exit(s);
}

void	ft_init_pixels(t_data *cub3d, t_image *image, int i)
{
	int	y;
	int	x;
	int	xx;

	y = 0;
	image->image_data = mlx_get_data_addr(image->image, \
	&image->bits_per_pixel, &image->size_line, &xx);
	while (y < 64)
	{
		x = 0;
		while (x < 64)
		{
			cub3d->texture_pixel[i][y * 64 + x] = \
			access_spes_pixel(image, x, y);
			x++;
		}
		y++;
	}
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
