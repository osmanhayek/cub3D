/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohayek <ohayek@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 13:38:11 by ohayek            #+#    #+#             */
/*   Updated: 2023/10/24 16:38:03 by ohayek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ft_init(t_data *cub3d)
{
	cub3d->floor = ft_calloc(1, sizeof(t_floor));
	cub3d->parser = ft_calloc(1, sizeof(t_parser));
	cub3d->player = ft_calloc(1, sizeof(t_player));
	cub3d->wall = ft_calloc(1, sizeof(t_wall));
	cub3d->mlx = ft_calloc(1, sizeof(t_mlx));
	cub3d->parser->arr_c = malloc(sizeof(int) * 3);
	cub3d->parser->arr_f = malloc(sizeof(int) * 3);
	cub3d->parser->arr_c[2] = -1;
	cub3d->parser->arr_f[2] = -1;
	cub3d->parser->textures = malloc(sizeof(t_image) * 4);
	cub3d->keycode[0] = 0;
	cub3d->keycode[1] = 0;
	cub3d->keycode[2] = 0;
	cub3d->keycode[3] = 0;
	cub3d->keycode[4] = 0;
	cub3d->keycode[5] = 0;
}

void	ft_parser(t_data *c, char *av)
{
	int	a;
	int	b;

	if (!cub_checker(av) && printf("Error\nMap .cub extention\n"))
		exit(1);
	take_path_and_cf(c, av);
	map_control(c->parser);
	check_link(c->parser);
	ft_init_mlx(c);
	world_map(c->parser, &c->parser->all_line[c->parser->map_begin]);
	c->parser->textures[0].image = \
	mlx_xpm_file_to_image(c->mlx->mlx_ptr, c->parser->no, &a, &b);
	ft_init_pixels(c, &c->parser->textures[0], 0);
	c->parser->textures[1].image = \
	mlx_xpm_file_to_image(c->mlx->mlx_ptr, c->parser->we, &a, &b);
	ft_init_pixels(c, &c->parser->textures[1], 1);
	c->parser->textures[2].image = \
	mlx_xpm_file_to_image(c->mlx->mlx_ptr, c->parser->ea, &a, &b);
	ft_init_pixels(c, &c->parser->textures[2], 2);
	c->parser->textures[3].image = \
	mlx_xpm_file_to_image(c->mlx->mlx_ptr, c->parser->so, &a, &b);
	ft_init_pixels(c, &c->parser->textures[3], 3);
	ft_init_player(c);
}

int	keyboard(t_data *data)
{
	double	move_speed;
	double	rot_speed;

	if ((data->keycode[0] || data->keycode[1]) && (data->keycode[2]
			|| data->keycode[3]))
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
	ft_raycasting(cub3d);
	return (0);
}

int	main(int ac, char **av)
{
	t_data	cub3d;

	if (ac == 2)
	{
		ft_init(&cub3d);
		ft_parser(&cub3d, av[1]);
		ft_raycasting(&cub3d);
		mlx_hook(cub3d.mlx->mlx_window, 2, 0, key_press, &cub3d);
		mlx_hook(cub3d.mlx->mlx_window, 3, 0, key_release, &cub3d);
		mlx_hook(cub3d.mlx->mlx_window, 17, 1L << 2, ft_exitt, &cub3d);
		mlx_loop_hook(cub3d.mlx->mlx_ptr, loop, &cub3d);
		mlx_loop(cub3d.mlx->mlx_ptr);
	}
	else
		printf("Error\nBad arguments\n");
	return (1);
}
