/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwojtasi <mwojtasi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 08:19:44 by mwojtasi          #+#    #+#             */
/*   Updated: 2023/12/12 04:17:11 by mwojtasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

t_list *get_next_line(int fd)
{
	static t_list *stash = NULL;
	size_t i;
	char *buffer;

	i = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = read_buffer(fd);
	while (!is_line(buffer))
	{
		append_buffer(&stash, buffer);
		buffer = read_buffer(fd);
	}
	append_buffer(&stash, buffer);
	return (stash);
}

char	*read_buffer(int fd)
{
	char	*buffer;
	size_t	read_bytes;
	
	buffer = malloc(BUFFER_SIZE + 1);
	if (buffer == NULL)
		return (NULL);
	buffer[BUFFER_SIZE] = '\0';
	read_bytes = read(fd, buffer, BUFFER_SIZE);
	if (read_bytes == 0)
		return (free(buffer), printf("eof") ,NULL);
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

t_list *append_buffer(t_list **stash, char *buffer)
{
	t_list *new;
	t_list *current;

	new = malloc(sizeof(t_list));
	if (new == NULL)
		return (NULL);
	new->str = buffer;
	new->next = NULL;
	if (*stash == NULL)
		*stash = new;
	else
	{
		current = *stash;
		while (current->next != NULL)
			current = current->next;
		current->next = new;
	}
	return (new);
} //move to utils

size_t str_list_len(t_list *list)
{
	size_t	count;
	size_t	i;
	t_list	*current;

	count = 0;
	i = 0;
	current = list;
	while (current != NULL)
	{
		if (current->next != NULL)
			count += BUFFER_SIZE;
		else
		{
			while (current->str[i])
				if (current->str[i++] == '\n')
					return (count + i);
			count += i;
		}
		current = current->next;
	}
	return (count);
}

//char *strcat_list(t_list *res)
//{
//	char 
//}

int main(int argc, char **argv)
{
    int fd;
	t_list *res;
	
    fd = open(argv[1], O_RDONLY);
    res = get_next_line(fd);
	printf("%zu", str_list_len(res));
	//get_next_line(fd);
    close(fd);
    return (0);
}

