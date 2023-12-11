/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwojtasi <mwojtasi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 08:19:44 by mwojtasi          #+#    #+#             */
/*   Updated: 2023/12/11 05:44:10 by mwojtasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

t_list *get_next_line(int fd)
{
	static t_list *stash = NULL;
	t_list *current;
	size_t i;

	i = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (i < BUFFER_SIZE)
	{
		current = append_buffer(stash, read_buffer(fd));
		printf("%s\n", current->str);
		if (is_line(current->str))
			return (stash);
		i++;
	}
	return (stash);
}

char	*read_buffer(int fd)
{
	char	*buffer;
	
	buffer = malloc(BUFFER_SIZE);
	read(fd, buffer, BUFFER_SIZE);
	return (buffer);
}

int is_line(char *buffer)
{
    size_t i = 0;

    while (i < BUFFER_SIZE && buffer[i])
    {
        if (buffer[i] == '\n')
            return (1);
        i++;
    }
    return (0);
}

t_list *append_buffer(t_list *stash, char *buffer)
{
	t_list *new;
	t_list *current;
	
	new = malloc(sizeof(t_list));
	if (new == NULL)
		return (NULL);
	new->str = buffer;
	new->next = NULL;
	if (stash == NULL)
		return (new);
	current = stash;
	while (current->next != NULL)
		current = current->next;
	current->next = new;
	return (new);
} //move to utils

int main(int argc, char **argv)
{
    int fd;

    fd = open(argv[1], O_RDONLY);
    get_next_line(fd);
    close(fd);
    return (0);
}

