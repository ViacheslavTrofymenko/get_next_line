/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viacheslav <viacheslav@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 10:51:39 by vtrofyme          #+#    #+#             */
/*   Updated: 2025/05/06 16:19:51 by vtrofyme       ###   ########.fr       */
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
			return (free(buff), free(left_str), NULL);
		if (bytes_read == 0)
			return (free(buff), left_str);
		buff[bytes_read] = '\0';
		if (!left_str)
		{
			left_str = (char *)malloc(1);
			left_str[0] = '\0';
		}
		left_str = ft_strjoin(left_str, buff);
	}
	free(buff);
	return (left_str);
}

char	*get_next_line(int fd)
{
	static char	*left_str;
	char		*next_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	left_str = ft_read_to_left_str(fd, left_str);
	if (!left_str)
	{
		return (NULL);
	}
	next_line = ft_get_line(left_str);
	left_str = ft_new_left_str(left_str);
	return (next_line);
}

int	main()
{
	int		fd = open("empty.txt", O_RDONLY);
	char	*line;

	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}
