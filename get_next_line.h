/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwojtasi <mwojtasi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 08:19:50 by mwojtasi          #+#    #+#             */
/*   Updated: 2023/12/11 05:07:42 by mwojtasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFFER_SIZE 5
# include <unistd.h>
# include <stdlib.h>
typedef struct s_list
{
	char *str;
	struct s_list *next;
} t_list;
t_list *get_next_line(int fd);
t_list *append_buffer(t_list *stash, char *buffer);
char	*read_buffer(int fd);
void display_list(t_list *head);
int is_line(char *buffer);
#endif