/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viacheslav <viacheslav@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 10:51:39 by vtrofyme          #+#    #+#             */
/*   Updated: 2025/05/05 21:10:29 by viacheslav       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

void	add_to_str_list(t_list **str_list, char *buff)
{
	t_list	*new_node;
	t_list	*last_node;

	last_node = find_last_node(*str_list);
	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return ;
	if (last_node == NULL)
		*str_list = new_node;
	else
		last_node->next = new_node;
	new_node->str_buff = buff;
	new_node->next = NULL;

}

void	copy_str(t_list *str_list, char *str)
{
	int	i;
	int	j;

	j = 0;
	while (str_list)
	{
		i = 0;
		while (str_list->str_buff[i])
		{
			if (str_list->str_buff[i] == '\n')
			{
				str[j++] = '\n';
				str[j] = '\0';
				return ;
			}
			str[j++] = str_list->str_buff[i++];
		}
		str_list = str_list->next;
	}
	str[j] = '\0';
}

void	create_str_list(t_list **str_list, int fd)
{
	ssize_t	bytes_read;
	char	*buff;

	while (!found_newline(*str_list))
	{
		buff = malloc(BUFFER_SIZE + 1);
		if (!buff)
			return ;
		bytes_read = read(fd, buff, BUFFER_SIZE);
		// TODO: check for -1
		if (!bytes_read)
		{
			free(buff);
			return ;
		}
		buff[bytes_read] = '\0';
		add_to_str_list(str_list, buff);
	}
}

char	*get_line(t_list *str_list)
{
	char	*next_str;
	int		str_len;

	str_len = len_to_newline(str_list);
	next_str = malloc(str_len + 1);
	if (!next_str)
		return (NULL);
	copy_str(str_list, next_str);
	return (next_str);
}

char	*get_next_line(int fd)
{
	static t_list	*str_list = NULL;
	char			*next_line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	create_str_list(&str_list, fd);
	if (!str_list)
		return (NULL);
	next_line = get_line(str_list);
	clean_str_list(&str_list);
	return (next_line);
}
/*
int	main()
{
	int		fd = open("file.txt", O_RDONLY);
	char	*line;

	while ((line = get_next_line(fd)) != NULL)
	{
		printf("BUFF => %s\n", line);
		free(line);
	}
	return (0);
}
*/
