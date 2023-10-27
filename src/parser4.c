/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohayek <ohayek@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 18:43:41 by  biekinci@s       #+#    #+#             */
/*   Updated: 2023/10/24 16:27:36 by ohayek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	is_there_two_or_more_map(char **map)
{
	int	i;

	i = -1;
	while (map[++i])
	{
		if (map[i][0] == '\n')
		{
			while (map[i] && map[i][0] == '\n')
				i++;
			if (map[i] && map[i][0] != '\0')
			{
				printf("Error\nmap_control\n");
				exit(1);
			}
			break ;
		}
	}
}

int	take_number(char *pieces, int y_i)
{
	int		number;
	char	character;
	int		x_i;

	x_i = -1;
	number = 0;
	while (pieces[++x_i] && pieces[x_i] != '\n')
	{
		character = pieces[x_i];
		if (character >= '0' && character <= '9' && y_i < 3)
			number = (number * 10) + (character - 48);
		else
		{
			printf("Error\nCF_control\n");
			exit(1);
		}
	}
	return (number);
}

char	*substring(char *str)
{
	int		i;
	int		letter_count;
	int		space_count;
	char	*new_str;

	i = 0;
	letter_count = -1;
	space_count = -1;
	while (str[++space_count] == ' ')
		i++;
	while (str[i] && str[i++] != ' ')
		++letter_count;
	if (str[i] && printf("Error\nsubstring\n"))
		exit(1);
	new_str = malloc(sizeof(char) * (letter_count + 1));
	i = -1;
	while (str[++i + space_count] && str[space_count + i] != ' '
		&& str[space_count + i] != '\n')
		new_str[i] = str[space_count + i];
	new_str[i] = '\0';
	return (new_str);
}

int	control_abc(t_data *info, char **all_line, int y, int *count_path)
{
	char	*str;

	str = all_line[y];
	if (ft_strnstr(str, "NO", 2))
		info->parser->no = substring(all_line[y] + 3);
	else if (ft_strnstr(str, "SO", 2))
		info->parser->so = substring(all_line[y] + 3);
	else if (ft_strnstr(str, "WE", 2))
		info->parser->we = substring(all_line[y] + 3);
	else if (ft_strnstr(str, "EA", 2))
		info->parser->ea = substring(all_line[y] + 3);
	else if (ft_strnstr(str, "C ", 2) || ft_strnstr(str, "F ", 2))
		take_cf(info->parser, all_line[y], 0);
	else
		return (0);
	*count_path += 1;
	return (1);
}
