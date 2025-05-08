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

#include "get_next_line_bonus.h"

static char	*update_buffer(char *buffer, int i)
{
	int	j;

	j = 0;
	if (!buffer)
		return (NULL);
	while (buffer[i] && buffer[i + 1] != '\0')
	{
		buffer[j] = buffer[i + 1];
		i++;
		j++;
	}
	while (buffer[j])
	{
		buffer[j] = 0;
		j++;
	}
	return (buffer);
}

static char	*get_line(char *buffer)
{
	int		i;
	char	*line;

	i = 0;
	if (*buffer == 0)
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	line = ft_calloc(i + 1, sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\0')
		line[i] = '\0';
	else if (buffer[i] == '\n')
		line[i] = '\n';
	buffer = update_buffer(buffer, i);
	return (line);
}

static char	*read_file(int fd, char *buffer)
{
	int		readed_bytes;
	char	*tmp_str;
	char	*tmp_buf;

	tmp_str = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!tmp_str)
		return (free(buffer), NULL);
	readed_bytes = 1;
	while (readed_bytes > 0)
	{
		readed_bytes = read(fd, tmp_str, BUFFER_SIZE);
		if (readed_bytes == -1)
			return (free(tmp_str), NULL);
		if (readed_bytes == 0)
			break ;
		tmp_buf = ft_strjoin(buffer, tmp_str);
		if (!tmp_buf)
			return (free(tmp_str), free(buffer), NULL);
		free(buffer);
		ft_memset(tmp_str, 0, BUFFER_SIZE + 1);
		buffer = tmp_buf;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (free(tmp_str), buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer[MAX_FD];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(buffer[fd]);
		buffer[fd] = NULL;
		return (NULL);
	}
	if (!buffer[fd])
		buffer[fd] = ft_calloc(1, 1);
	if (!buffer[fd])
		return (NULL);
	buffer[fd] = read_file(fd, buffer[fd]);
	if (!buffer[fd])
		return (NULL);
	line = get_line(buffer[fd]);
	if (line == NULL)
	{
		free(buffer[fd]);
		buffer[fd] = NULL;
	}
	return (line);
}
