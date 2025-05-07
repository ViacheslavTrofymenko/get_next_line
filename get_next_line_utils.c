/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viacheslav <viacheslav@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 10:52:21 by vtrofyme          #+#    #+#             */
/*   Updated: 2025/05/05 18:18:30 by viacheslav       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_list	*find_last_node(t_list *str_list)
{
	if (!str_list)
		return (NULL);
	while (str_list->next)
		str_list = str_list->next;
	return (str_list);
}

void	free_list(t_list **str_list, t_list *clean_node, char *buff)
{
	t_list	*temp;

	while (*str_list)
	{
		temp = (*str_list)->next;
		free((*str_list)->str_buff);
		free(*str_list);
		*str_list = temp;
	}
	*str_list = NULL;
	if (clean_node->str_buff[0])
		*str_list = clean_node;
	else
	{
		free(buff);
		free(clean_node);
	}
}

int	len_to_newline(t_list *str_list)
{
	int	i;
	int	len;

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

int	found_newline(t_list *str_list)
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

void	clean_str_list(t_list **str_list)
{
	t_list	*last_node;
	t_list	*clean_node;
	int		i;
	int		j;
	char	*buff;

	buff = malloc(BUFFER_SIZE + 1);
	clean_node = malloc(sizeof(t_list));
	if (!buff || !clean_node)
		return ;
	last_node = find_last_node(*str_list);
	i = 0;
	j = 0;
	while (last_node->str_buff[i] != '\0' && last_node->str_buff[i] != '\n')
		i++;
	while (last_node->str_buff[i] != '\0' && last_node->str_buff[++i])
		buff[j++] = last_node->str_buff[++i];
	buff[j] = '\0';
	clean_node->str_buff = buff;
	clean_node->next = NULL;
	free_list(str_list, clean_node, buff);
}
