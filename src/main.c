/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohayek <ohayek@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 13:38:11 by ohayek            #+#    #+#             */
/*   Updated: 2023/10/22 00:57:56 by ohayek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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

int	ft_exit(int s, t_data *cub3d)
{
	exit(s);
}

void	ft_init_pixels(t_data *cub3d, t_image *image, int i)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	int xx;
	image->image_data = mlx_get_data_addr(image->image, &image->bits_per_pixel, &image->size_line, &xx);
	while (y < 64)
	{
		while (x < 64)
		{
			cub3d->texture_pixel[i][y * 64 + x] = access_spes_pixel(image, x, y);
			x++;
		}
		y++;
	}
}

void	ft_init(t_data *cub3d)
{
	cub3d->floor = malloc(sizeof(t_floor));
	cub3d->parser = malloc(sizeof(t_parser));
	cub3d->player = malloc(sizeof(t_player));
	cub3d->wall = malloc(sizeof(t_wall));
	cub3d->mlx = malloc(sizeof(t_mlx));
}

void	ft_parser(t_data *cub3d)
{
	t_parser	*p;

	p = cub3d->parser;
	p->world_map = malloc(sizeof(int *) * 10);
	for (int i = 0; i < 10; i++)
		p->world_map[i] = malloc(sizeof(int) * 10);
	for (int i = 0; i < 10; i++)
	{
		p->world_map[0][i] = 1;
		p->world_map[9][i] = 1;
	}
	for (int i = 1; i < 9; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (!j || j == 9)
				p->world_map[i][j] = 1;
			else
				p->world_map[i][j] = 0;
		}
	}
	p->world_map[1][3] = 1;
	p->world_map[3][4] = 1;
	p->world_map[1][4] = 1;
	p->world_map[3][3] = 1;
	p->pos_x = 6.0;
	p->pos_y = 6.0;
	p->p = 'N';
	p->color_c = 0x9A752D;
	p->color_f = 0x87ceeb;
	p->textures = malloc(sizeof(t_image) * 4);
	int tw, th;
	p->textures[0].image = mlx_xpm_file_to_image(cub3d->mlx->mlx_ptr, "bluestone.xpm", &tw, &th);
	p->textures[1].image = mlx_xpm_file_to_image(cub3d->mlx->mlx_ptr, "bluestone.xpm", &tw, &th);
	p->textures[2].image = mlx_xpm_file_to_image(cub3d->mlx->mlx_ptr, "bluestone.xpm", &tw, &th);
	p->textures[3].image = mlx_xpm_file_to_image(cub3d->mlx->mlx_ptr, "bluestone.xpm", &tw, &th);
	ft_init_pixels(cub3d, &p->textures[0], 0);
	ft_init_pixels(cub3d, &p->textures[1], 1);
	ft_init_pixels(cub3d, &p->textures[2], 2);
	ft_init_pixels(cub3d, &p->textures[3], 3);
	ft_init_player(cub3d);
	cub3d->keycode[0] = 0;
	cub3d->keycode[1] = 0;
	cub3d->keycode[2] = 0;
	cub3d->keycode[3] = 0;
	cub3d->keycode[4] = 0;
	cub3d->keycode[5] = 0;
}

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
		ft_exit(0, NULL);
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
		ft_exit(0, NULL);
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
		y += cub3d->player->dir_y * move_speed;
	}
	else
	{
		x -= cub3d->player->dir_x * move_speed;
		y -= cub3d->player->dir_y * move_speed;
	}
	if (cub3d->parser->world_map[(int)y][(int)x] == 1)
	{
		return (1);
	}
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
	cub3d->player->dir_y = old_dir_x * sin(rot_speed)
		+ cub3d->player->dir_y * cos(rot_speed);
	cub3d->player->plane_x = cub3d->player->plane_x * cos(rot_speed)
		- cub3d->player->plane_y * sin(rot_speed);
	cub3d->player->plane_y = old_plane_x * sin(rot_speed)
		+ cub3d->player->plane_y * cos(rot_speed);
}

int	calc_move_d(t_data *cub3d, int sign, double move_speed)
{
	double	x;
	double	y;

	if (sign == 1)
	{
		x = cub3d->player->pos_x + cub3d->player->plane_x * move_speed;
		y = cub3d->player->pos_y + cub3d->player->plane_y * move_speed;
	}
	else
	{
		x = cub3d->player->pos_x - cub3d->player->plane_x * move_speed;
		y = cub3d->player->pos_y - cub3d->player->plane_y * move_speed;
	}
	if (cub3d->parser->world_map[(int)y][(int)x] == 1)
		return (1);
	cub3d->player->pos_x = x;
	cub3d->player->pos_y = y;
	return (0);
}

int	keyboard(t_data *data)
{
	double	move_speed;
	double	rot_speed;

	if ((data->keycode[0] || data->keycode[1])
		&& (data->keycode[2] || data->keycode[3]))
		move_speed = (0.09 / sqrt(2));
	else
		move_speed = 0.09;
	rot_speed = 0.09;
	if (data->keycode[0] && calc_move(data, 1, move_speed))
		return (0);
	else if (data->keycode[1] && calc_move(data, -1, move_speed))
		return (0);
	else if (data->keycode[2] && calc_move_d(data, -1, move_speed))
		return (0);
	else if (data->keycode[3] && calc_move_d(data, 1, move_speed))
		return (0);
	else if (data->keycode[4])
		calc_rot(data, -rot_speed);
	else if (data->keycode[5])
		calc_rot(data, rot_speed);
	return (0);
}

int	loop(t_data *cub3d)
{
	keyboard(cub3d);
	ft_fill_image_black(cub3d);
	ft_raycasting(cub3d);
	return (0);
}

int	main(int ac, char **av)
{
	t_data	cub3d;

	if (ac == 2)
	{
		ft_init(&cub3d);
		ft_init_mlx(&cub3d);
		ft_parser(&cub3d);
		ft_raycasting(&cub3d);
		mlx_hook(cub3d.mlx->mlx_window, 2, 0, key_press, &cub3d);
		mlx_hook(cub3d.mlx->mlx_window, 3, 0, key_release, &cub3d);
		mlx_hook(cub3d.mlx->mlx_window, 17, 1L << 2, ft_exit, NULL);
		mlx_loop_hook(cub3d.mlx->mlx_ptr, loop, &cub3d);
		mlx_loop(cub3d.mlx->mlx_ptr);
	}
	printf("Error-> Bad argumetns\n");
	return (1);
}
