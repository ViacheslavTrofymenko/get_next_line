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

void	free_list(t_list **buf_list)
{
	t_list	*temp;

	while (*buf_list)
	{
		temp = (*buf_list)->next;
		free((*buf_list)->str_buf);
		free(*buf_list);
		*buf_list = temp;
	}
}

void	trim_buflist(t_list **buf_list)
{
	t_list	*last_node;
	t_list	*new_node;
	int		i = 0;
	int		j = 0;
	char	*buf;

	if (!buf_list || !*buf_list)
		return ;

	last_node = find_last_node(*buf_list);
	while (last_node->str_buf[i] && last_node->str_buf[i] != '\n')
		i++;

	if (!last_node->str_buf[i])
	{
		free_list(buf_list);
		return ;
	}

	buf = malloc(ft_strlen(last_node->str_buf + i));
	new_node = malloc(sizeof(t_list));
	if (!buf || !new_node)
	{
		free(buf);
		free(new_node);
		return ;
	}

	i++; // move past '\n'
	while (last_node->str_buf[i])
		buf[j++] = last_node->str_buf[i++];
	buf[j] = '\0';

	new_node->str_buf = buf;
	new_node->next = NULL;

	free_list(buf_list); // Очистить старый список
	*buf_list = new_node; // Заменить новым
}

void	add_to_buflist(t_list **buf_list, char *buf)
{
	t_list	*new_node;
	t_list	*last_node;

	new_node = (t_list *)malloc(sizeof(t_list));
	if (!new_node)
		return ;
	new_node->str_buf = buf;
	new_node->next = NULL;
	if (*buf_list == NULL)
		*buf_list = new_node;
	else
	{
		last_node = *buf_list;
		while (last_node->next)
			last_node = last_node->next;
		last_node->next = new_node;
	}
}
void	copy_str(t_list *buf_list, char *str)
{
	int	i;
	int	k;

	if (buf_list == NULL)
		return ;
	k = 0;
	while (buf_list)
	{
		i = 0;
		while (buf_list->str_buf[i])
		{
			if (buf_list->str_buf[i] == '\n')
			{
				str[k++] = '\n';
				str[k] = '\0';
				return ;
			}
			str[k++] = buf_list->str_buf[i++];
		}
		buf_list = buf_list->next;
	}
	str[k] = '\0';
}

int	found_newline(t_list *buf_list)
{
	while (buf_list)
	{
		if (ft_strchr(buf_list-> str_buf, '\n'))
			return (1);
			buf_list = buf_list->next;
	}
	return (0);
}

void	read_to_buflist(t_list **buf_list, int fd)
{
	ssize_t		bytes_read;
	char		*buf;

	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return ;
	while (!found_newline(buf_list))
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read <= 0)
		{
			free(buf);
			return ;
		}
		buf[bytes_read] = '\0';
		add_to_buflist(buf_list, ft_strdup(buf));
	}
	free(buf);
	}
int	len_to_newline(t_list *buf_list)
{
	int	i;
	int	len;

	len = 0;
	while (buf_list)
	{
		i = 0;
		while (buf_list->str_buf[i])
		{
			if (buf_list->str_buf[i] == '\n')
			{
				len++;
				return (len);
			}
			i++;
			len++;
		}
		buf_list = buf_list->next;
	}
	return (len);
}

char	*get_line(t_list *buf_list)
{
	char	*next_str;
	int		str_len;

	if (buf_list == NULL)
		return (NULL);
	str_len = len_to_newline(buf_list);
	next_str = malloc(str_len + 1);
	if (!next_str)
		return (NULL);
	copy_str(buf_list, next_str);
	return (next_str);
}

char	*get_next_line(int fd)
{
	static t_list	*buf_list;
	char			*next_line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	read_to_buflist(&buf_list, fd);
	if (buf_list == NULL)
		return (NULL);
	next_line = get_line(buf_list);
	trim_buflist(&buf_list);
	return (next_line);
}

/*
int fd = open("file.txt", O_RDONLY);
char *line;

while ((line = get_next_line(fd)) != NULL)
{
    printf("%s", line);
    free(line);
}
close(fd);
*/

