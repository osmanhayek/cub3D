/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohayek <ohayek@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 18:41:16 by  biekinci@s       #+#    #+#             */
/*   Updated: 2023/10/24 16:23:00 by ohayek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	map_max_line(char **map)
{
	size_t	max_len;
	size_t	y;

	y = 0;
	max_len = 0;
	while (map[y])
	{
		if (max_len < ft_strlen(map[y]))
			max_len = ft_strlen(map[y]);
		y++;
	}
	return (max_len);
}

int	find_element(char *str, char *str2)
{
	int	y;

	y = -1;
	while (str[++y] && str[y] != '\n')
	{
		if (ft_strchr(str2, str[y]))
			return (1);
	}
	return (0);
}

int	map_line_count(char **map)
{
	int	line_len;

	line_len = 0;
	while (map[line_len])
		line_len++;
	return (line_len);
}

int	comma_control(char *str)
{
	int	count;
	int	index;

	count = 0;
	index = -1;
	while (str[++index])
		if (str[index] == ',')
			count++;
	if (count > 2)
		return (0);
	return (1);
}

char	**read_map(char *path)
{
	int		fd;
	int		line_count;
	char	*line;
	char	**all_line;
	int		index;

	line_count = 0;
	index = 0;
	fd = open(path, O_RDONLY);
	if (fd == -1 && printf("Error\n.cub file not found\n"))
		exit(1);
	line = get_next_line(fd);
	while (line)
	{
		++line_count;
		free(line);
		line = get_next_line(fd);
	}
	all_line = malloc(sizeof(char *) * (line_count + 1));
	close(fd);
	fd = open(path, O_RDONLY);
	while (index < line_count)
		all_line[index++] = get_next_line(fd);
	all_line[index] = NULL;
	return (all_line);
}
