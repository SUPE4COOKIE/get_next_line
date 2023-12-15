/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwojtasi <mwojtasi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 08:19:44 by mwojtasi          #+#    #+#             */
/*   Updated: 2023/12/15 03:19:42 by mwojtasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

void free_stash(t_list **stash) {
	t_list *tmp;

	while (*stash) {
		tmp = (*stash)->next;
		free((*stash)->str);
		free(*stash);
		*stash = tmp;
	}
}

char *get_next_line(int fd)
{
	static t_list *stash = NULL;
	size_t i;
	char *buffer;

	i = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = read_buffer(fd);
	while (buffer && !is_line(buffer))
	{
		append_buffer(&stash, buffer);
		free(buffer);
		buffer = read_buffer(fd);
	}
	if (buffer)
		append_buffer(&stash, buffer);
	free(buffer);
	return (strcat_list(&stash));
}

char	*read_buffer(int fd)
{
	char	*buffer;
	size_t	read_bytes;
	
	buffer = malloc(BUFFER_SIZE + 1);
	if (buffer == NULL)
		return (NULL);
	read_bytes = read(fd, buffer, BUFFER_SIZE);
	if (read_bytes <= 0)
		return (free(buffer), NULL);
	buffer[read_bytes] = '\0';
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
	new->str = strdup(buffer);
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
}

size_t str_list_len(t_list *list)
{
	size_t	count;
	size_t	i;
	t_list	*current;

	count = 0;
	current = list;
	while (current != NULL)
	{
		i = 0;
		while (current->str[i])
			if (current->str[i++] == '\n')
				return (count + i);
		count += i;
		current = current->next;
	}
	return (count);
}


void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;

	if (!dest && !src)
		return (NULL);
	if (dest < src)
	{
		i = 0;
		while (n--)
		{
			((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
			i++;
		}
	}
	else
	{
		while (n > 0)
		{
			n--;
			((unsigned char *)dest)[n] = ((unsigned char *)src)[n];
		}
	}
	return (dest);
}

int strcat_untiln(char *dest, char **src)
{
	size_t i;
	size_t j;

	if (!dest || !src || !*src)
        return (1);
	i = 0;
	j = 0;
	while (dest[i])
		i++;
	while ((*src)[j] && (*src)[j] != '\n')
		dest[i++] = (*src)[j++];
	if ((*src)[j] == '\n')
	{
		dest[i++] = (*src)[j++];
		ft_memmove(*src, *src + j, strlen(*src + j) + 1);
		dest[i] = '\0';
		return (1);
	}
	dest[i] = '\0';
	return (0);
}

char *strcat_list(t_list **res)
{
    char *str;
    t_list *tmp_list;
    size_t len;

    len = str_list_len(*res);
    str = malloc(len + 1);
    if (str == NULL)
        return (NULL);
    str[0] = '\0';
    while (strcat_untiln(str, &((*res)->str)) == 0)
    {
        tmp_list = (*res)->next;
        free((*res)->str);
        free(*res);
        *res = tmp_list;
    }
    return (str);
}


int main(int argc, char **argv)
{
    int fd;
	char *line;	
	
    fd = open(argv[1], O_RDONLY);
	line = get_next_line(fd);
    printf("%s", line);
	free(line);
	line = get_next_line(fd);
    printf("%s", line);
    free(line);
	line = get_next_line(fd);
    printf("%s", line);
    free(line);
	line = get_next_line(fd);
	printf("%s", line);
	free(line);
    close(fd);
    return (0);
}

