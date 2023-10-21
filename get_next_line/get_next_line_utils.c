/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohayek <ohayek@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 18:03:39 by ohayek            #+#    #+#             */
/*   Updated: 2023/07/06 18:03:39 by ohayek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlenn(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	i++;
	return (i);
}

char	*ft_append(char *s1, char *s2)
{
	char	*result;
	size_t	i;
	size_t	j;

	i = 0;
	if (!s1)
	{
		result = (char *)malloc(sizeof(char) * ft_strlenn(s2) + 1);
		if (!result)
			return (NULL);
		ft_strcpy(result, s2);
		free(s2);
		return (result);
	}
	j = 0;
	result = (char *)malloc(sizeof(char) * (ft_strlenn(s1) + ft_strlenn(s2)) + 1);
	if (!result)
		return (NULL);
	while (s1[j])
		result[i++] = s1[j++];
	ft_strcpy(result + i, s2);
	free(s1);
	free(s2);
	return (result);
}

size_t	founded_next_line(char *res)
{
	size_t	i;

	if (!res)
		return (0);
	i = 0;
	while (res[i])
	{
		if (res[i] == '\n')
			return (i + 1);
		i++;
	}
	return (0);
}

size_t	len_to_next_line(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (i + 1);
		i++;
	}
	return (i);
}

char	*find_line(char *res)
{
	char	*line;
	size_t	size;
	size_t	i;

	if (!res)
		return (NULL);
	size = len_to_next_line(res);
	line = (char *)malloc(sizeof(char) * size + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (res[i])
	{
		line[i] = res[i];
		if (res[i] == '\n')
		{
			line[++i] = '\0';
			return (line);
		}
	i++;
	}
	line[i] = '\0';
	return (line);
}
