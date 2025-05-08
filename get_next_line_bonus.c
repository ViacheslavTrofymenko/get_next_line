/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrofyme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:00:45 by vtrofyme          #+#    #+#             */
/*   Updated: 2025/05/08 15:00:48 by vtrofyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

char	*ft_read_to_left_str(int fd, char *left_str)
{
	char	*buff;
	ssize_t	bytes_read;

	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	bytes_read = 1;
	while (!ft_strchr(left_str, '\n') && bytes_read != 0)
	{
		bytes_read = read(fd, buff, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buff);
			free(left_str);
			return (NULL);
		}
		buff[bytes_read] = '\0';
		left_str = ft_strjoin(left_str, buff);
	}
	free(buff);
	return (left_str);
}

char	*get_next_line(int fd)
{
	static char	*left_str[MAX_FD];
	char		*next_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	left_str[fd] = ft_read_to_left_str(fd, left_str[fd]);
	if (!left_str[fd])
	{
		return (NULL);
	}
	next_line = ft_get_line(left_str[fd]);
	left_str[fd] = ft_new_left_str(left_str[fd]);
	return (next_line);
}
