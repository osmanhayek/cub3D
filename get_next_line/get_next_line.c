/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohayek <ohayek@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 18:31:55 by ohayek            #+#    #+#             */
/*   Updated: 2023/07/06 18:31:55 by ohayek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_strcpy(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	while (s2[i])
	{
		s1[i] = s2[i];
		i++;
	}
	s1[i] = '\0';
}

void	create_res(char **res, int fd)
{
	char	*buf;
	size_t	read_tracker;

	while (!founded_next_line(*res))
	{
		buf = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
		if (!buf)
			return ;
		read_tracker = read(fd, buf, BUFFER_SIZE);
		if (!read_tracker)
		{
			free(buf);
			return ;
		}
		buf[read_tracker] = '\0';
		*res = ft_append(*res, buf);
	}
}

char	*clean_res(char *res)
{
	char	*new_buf;
	size_t	i;
	size_t	k;

	i = len_to_next_line(res);
	if (!res[i])
	{
		free(res);
		return (NULL);
	}
	new_buf = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!new_buf)
		return (NULL);
	k = 0;
	while (res[i])
		new_buf[k++] = res[i++];
	new_buf[k] = '\0';
	free(res);
	return (new_buf);
}

char	*get_next_line(int fd)
{
	static char	*res = NULL;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		if (res)
			free(res);
		res = NULL;
		return (NULL);
	}
	create_res(&res, fd);
	if (!res)
		return (NULL);
	line = find_line(res);
	res = clean_res(res);
	return (line);
}
