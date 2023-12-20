/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwojtasi <mwojtasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 08:19:50 by mwojtasi          #+#    #+#             */
/*   Updated: 2023/12/19 20:45:13 by mwojtasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

typedef struct s_list
{
	char			*str;
	struct s_list	*next;
}					t_list;
void				free_stash(t_list **stash);
void				*ft_memmove(void *dest, const void *src, size_t n);
char				*ft_strdup(char *src);
char				*get_next_line(int fd);
t_list				*append_buffer(t_list **stash, char *buffer);
char				*read_buffer(int fd, t_list **stash);
size_t				str_list_len(t_list *list);
int					strcat_untiln(char *dest, char **src);
int					is_line(char *buffer);
char				*strcat_list(t_list **res);
#endif