/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohayek <ohayek@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 18:41:45 by  biekinci@s       #+#    #+#             */
/*   Updated: 2023/10/24 16:23:40 by ohayek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	any_different_character(char **map)
{
	size_t	y;
	size_t	x;

	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (map[y][x] == '\t' || (!ft_strchr("WSEN01 ", map[y][x])
					&& map[y][x] != '\n'))
			{
				printf("map[y][x] = %s\n", map[y]);
				return (1);
			}
		}
	}
	return (0);
}

int	**map_assign(t_parser *parser, char **map, int **worldMap, int y)
{
	int	x;

	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (ft_strchr("1 ", map[y][x]))
				worldMap[y][x] = 1;
			else if (map[y][x] == '0')
				worldMap[y][x] = 0;
			else if (ft_strchr("WSEN", map[y][x]))
			{
				worldMap[y][x] = 0;
				parser->p = map[y][x];
				parser->pos_x = x;
				parser->pos_y = y;
			}
			else
				worldMap[y][x] = 1;
		}
	}
	return (worldMap);
}

void	world_map(t_parser *parser, char **map)
{
	int	y;
	int	line_count;
	int	max_len;
	int	**world_map;

	line_count = map_line_count(map);
	max_len = map_max_line(map);
	y = -1;
	world_map = ft_calloc(sizeof(int *), (line_count));
	while (++y < line_count)
		world_map[y] = ft_calloc(sizeof(int), max_len);
	world_map = map_assign(parser, map, world_map, 0);
	parser->line_max = line_count;
	parser->column_max = max_len;
	parser->world_map = world_map;
	parser->color_f = (parser->arr_c[0] * 256 * 256) + \
	(parser->arr_c[1] * 256) + (parser->arr_c[2]);
	parser->color_c = (parser->arr_f[0] * 256 * 256) + \
	(parser->arr_f[1] * 256) + (parser->arr_f[2]);
}

int	xpm_checker(char *a)
{
	unsigned int	i;

	i = 0;
	while (a[i])
		i++;
	if (i > 4 && a[i - 1] == 'm' && a[i - 2] == 'p' && a[i - 3] == 'x' && \
		a[i - 4] == '.' && a[i - 5] != '/')
		return (1);
	return (0);
}

void	check_link(t_parser *parser)
{
	if (!xpm_checker(parser->ea) || !xpm_checker(parser->no)
		|| !xpm_checker(parser->so) || !xpm_checker(parser->we))
	{
		printf("Error\n.xpm extension\n");
		exit(1);
	}
	if (open(parser->ea, O_RDONLY) == -1 || open(parser->no, O_RDONLY) == -1
		|| open(parser->so, O_RDONLY) == -1 || open(parser->we, O_RDONLY) == -1)
	{
		printf("Error\n.xpm file\n");
		exit(1);
	}
}
