/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohayek <ohayek@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 14:14:30 by  biekinci@s       #+#    #+#             */
/*   Updated: 2023/10/24 16:22:29 by ohayek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	is_surronded_by_wall(char **map, int x, int line_len, int column_len)
{
	int	count_flag;
	int	y;

	y = -1;
	count_flag = 0;
	line_len = map_line_count(map);
	while (map[++y])
	{
		column_len = ft_strlen(map[y]);
		x = -1;
		while (++x < column_len)
		{
			if (ft_strchr("WSEN", map[y][x]))
				count_flag++;
			if (ft_strchr("NWSE0", map[y][x]))
				if (((y == 0 || x == 0 || line_len == y + 1 || column_len == x
							+ 1) || func(map, y, x)) \
							&& printf("Error\nmap_control\n"))
					exit(1);
		}
	}
	if (count_flag != 1 && printf("Error\nmap_control\n"))
		exit(1);
	return (y);
}

void	map_control(t_parser *parser)
{
	char	**map;
	int		line_len;
	int		column_len;
	int		y;

	column_len = -1;
	line_len = 0;
	map = &(parser->all_line[parser->map_begin]);
	is_there_two_or_more_map(map);
	if (any_different_character(map) && printf("Error\ndifferent_character\n"))
		exit(1);
	map = padding_map(parser, -1, -1);
	line_len = map_line_count(map);
	y = is_surronded_by_wall(map, -1, line_len, column_len);
	if (y > 0 && map[y - 1][0] == '*' && printf("Error\nmap_control\n"))
		exit(1);
	y = -1;
	while (map[++y])
		free(map[y]);
	free(map);
}

void	take_cf(t_parser *parser, char *CF, int number)
{
	int		y_i;
	char	**pieces;
	char	*p;

	y_i = -1;
	if (!comma_control(CF) && printf("Error\ncomma_control\n"))
		exit(1);
	pieces = ft_split(CF + 2, ',');
	while (pieces[++y_i])
	{
		if (pieces[y_i][0] == '\n' && printf("Error\nCF_control\n"))
			exit(1);
		p = ft_strtrim(pieces[y_i], " ");
		number = take_number(p, y_i);
		if (number > 255 && printf("Error\nCF number control\n"))
			exit(1);
		if (CF[0] == 'C')
			parser->arr_c[y_i] = number;
		else if (CF[0] == 'F')
			parser->arr_f[y_i] = number;
		free(pieces[y_i]);
		free(p);
	}
	free(pieces);
}

void	is_full_path_and_cf(t_data *info, int count_path)
{
	if (!info->parser->ea || !info->parser->no || !info->parser->so
		|| !info->parser->we || count_path != 6 || info->parser->arr_c[2] == -1
		|| info->parser->arr_f[2] == -1)
	{
		printf("Error\nMap elements...\n");
		exit(1);
	}
}

void	take_path_and_cf(t_data *info, char *path)
{
	char	**all_line;
	int		count_path;
	int		y;

	y = -1;
	count_path = 0;
	all_line = read_map(path);
	info->parser->all_line = all_line;
	if (!find_map(info->parser) && printf("Error\n couldn't find map\n"))
		exit(1);
	while (++y < info->parser->map_begin)
	{
		if (control_abc(info, all_line, y, &count_path)
			|| all_line[y][0] == '\n')
			continue ;
		else
		{
			printf("Error\nMap elements...\n");
			exit(1);
		}
		++count_path;
	}
	is_full_path_and_cf(info, count_path);
}
