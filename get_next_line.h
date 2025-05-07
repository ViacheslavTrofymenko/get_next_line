/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viacheslav <viacheslav@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 10:53:01 by vtrofyme          #+#    #+#             */
/*   Updated: 2025/05/05 18:18:45 by viacheslav       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <unistd.h>
# include <stdlib.h>

typedef struct s_list
{
	char			*str_buff;
	struct s_list	*next;
}	t_list;

char	*get_next_line(int fd);
t_list	*find_last_node(t_list *str_list);
void	free_list(t_list **str_list, t_list *clean_node, char *buff);
int		len_to_newline(t_list *str_list);
int		found_newline(t_list *str_list);
void	clean_str_list(t_list **str_list);

#endif
