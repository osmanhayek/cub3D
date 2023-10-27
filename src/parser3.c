/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohayek <ohayek@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 18:42:52 by  biekinci@s       #+#    #+#             */
/*   Updated: 2023/10/24 16:27:20 by ohayek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	cub_checker(char *a)
{
	unsigned int	i;

	i = 0;
	while (a[i])
		i++;
	if (i > 4 && a[i - 1] == 'b' && a[i - 2] == 'u' && a[i - 3] == 'c' && \
		a[i - 4] == '.' && a[i - 5] != '/')
		return (1);
	return (0);
}

int	func(char **map, int y, int x)
{
	if (!ft_strchr("10NEWS", map[y + 1][x]) || !ft_strchr("10NEWS", map[y
			- 1][x]) || !ft_strchr("10NEWS", map[y][x - 1])
		|| !ft_strchr("10NEWS", map[y][x + 1]))
	{
		printf("Error\n map control\n");
		return (1);
	}
	return (0);
}

char	**create_new_map(char **new_map, char **map, int max_line,
		int max_column)
{
	int	x;
	int	y;

	y = -1;
	while (++y < max_line)
	{
		x = -1;
		while (map[y][++x] && map[y][x] != '\n')
			new_map[y][x] = map[y][x];
		while (x < max_column - 1)
			new_map[y][x++] = '*';
		new_map[y][x] = '\n';
		new_map[y][++x] = '\0';
	}
	return (new_map);
}

char	**padding_map(t_parser *parser,	int x, int y)
{
	int		max_column;
	int		max_line;
	char	**new_map;
	char	**map;

	y = 0;
	x = 0;
	map = &(parser->all_line[parser->map_begin]);
	max_column = map_max_line(map);
	max_line = map_line_count(map);
	new_map = calloc(sizeof(char *), max_line + 2);
	while (y < max_line + 1)
		new_map[y++] = calloc(sizeof(char), (max_column + 1));
	new_map[max_line + 1] = NULL;
	y = -1;
	new_map = create_new_map(new_map, map, max_line, max_column);
	while (x < max_column)
		new_map[max_line][x++] = '-';
	new_map[max_line][max_column] = '\0';
	return (new_map);
}

int	find_map(t_parser *parser)
{
	int		y;
	size_t	x;
	int		character;

	y = -1;
	while (parser->all_line[++y])
	{
		x = 0;
		character = parser->all_line[y][x];
		while (character && ft_strchr("WESN10 ", character))
		{
			x++;
			character = parser->all_line[y][x];
		}
		if (ft_strlen(parser->all_line[y]) - 1 == x && x > 0)
		{
			parser->map_begin = y;
			break ;
		}
	}
	if (parser->map_begin == 0)
		return (0);
	return (1);
}
