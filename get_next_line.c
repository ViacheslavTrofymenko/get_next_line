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

t_list *find_last_node(t_list *str_list)
{
	if (!str_list)
		return (NULL);
	while (str_list->next)
		str_list = str_list->next;
	return (str_list);
}

void free_list(t_list **str_list)
{
	t_list *temp;

	while (*str_list)
	{
		temp = (*str_list)->next;
		free((*str_list)->str_buff);
		free(*str_list);
		*str_list = temp;
	}
}

void clean_str_list(t_list **str_list)
{
	t_list *last_node;
	t_list *clean_node;
	int i;
	int j;
	char *buff;

	buff = malloc(BUFFER_SIZE + 1);
	clean_node = malloc(sizeof(t_list));
	if (!buff || !clean_node)
		return ;
	last_node = find_last_node(str_list);
	i = 0;
	j = 0;
	while (last_node->str_buff[i] != '\0' && last_node->str_buff[i] != '\n')
		i++;
	while (last_node->str_buff[i] != '\0' && last_node->str_buff[++i])
		buff[j++] = last_node->str_buff[++i];
	buff[j] = '\0';
	clean_node->str_buff = buff;
	clean_node->next = NULL;
	ft_free(str_list, clean_node, buff);
}

void add_to_str_list(t_list **str_list, char *buff)
{
	t_list *new_node;
	t_list *last_node;

	last_node = find_last_node(*str_list);
	new_node = (t_list *)malloc(sizeof(t_list));
	if (!new_node)
		return;
	new_node->str_buff = buff;
	new_node->next = NULL;
	if (*str_list == NULL)
		*str_list = new_node;
	else
	{
		last_node = *str_list;
		while (last_node->next)
			last_node = last_node->next;
		last_node->next = new_node;
	}
}
void copy_str(t_list *str_list, char *str)
{
	int i;
	int j;

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

int found_newline(t_list *str_list)
{
	int	i;
	while (str_list)
	{
		i = 0;
		while (str_list->str_buff[i] && i < BUFFER_SIZE)
		{
			if (str_list->str_buff[i] == '\n')
				return (1);
			i++;
		}
		str_list = str_list->next;
	}
	return (0);
}

void create_str_list(t_list **str_list, int fd)
{
	ssize_t bytes_read;
	char *buff;

	while (!found_newline(*str_list))
	{
		buff = malloc(BUFFER_SIZE + 1);
		if (!buff)
			return;
		bytes_read = read(fd, buff, BUFFER_SIZE);
		// TODO: check for -1
		if (!bytes_read)
		{
			free(buff);
			return;
		}
		buff[bytes_read] = '\0';
		add_to_str_list(str_list, ft_strdup(buff));
	}
	free(buff);
}
int len_to_newline(t_list *str_list)
{
	int i;
	int len;

	len = 0;
	while (str_list)
	{
		i = 0;
		while (str_list->str_buff[i])
		{
			if (str_list->str_buff[i] == '\n')
			{
				len++;
				return (len);
			}
			i++;
			len++;
		}
		str_list = str_list->next;
	}
	return (len);
}

char *get_line(t_list *str_list)
{
	char *next_str;
	int str_len;

	str_len = len_to_newline(str_list);
	next_str = malloc(str_len + 1);
	if (!next_str)
		return (NULL);
	copy_str(str_list, next_str);
	return (next_str);
}

char *get_next_line(int fd)
{
	static t_list *str_list = NULL;
	char *next_line;

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
	close(fd);
	return (0);
}
*/
