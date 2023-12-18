/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwojtasi <mwojtasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 08:19:44 by mwojtasi          #+#    #+#             */
/*   Updated: 2023/12/18 17:22:24 by mwojtasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_list	*stash = NULL;
	char			*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = read_buffer(fd, &stash);
	while (buffer && !is_line(buffer))
	{
		append_buffer(&stash, buffer);
		free(buffer);
		buffer = read_buffer(fd, &stash);
	}
	if (buffer)
	{
		append_buffer(&stash, buffer);
		free(buffer);
	}
	return (strcat_list(&stash));
}

char	*read_buffer(int fd, t_list **stash)
{
	char	*buffer;
	int		read_bytes;

	buffer = malloc(BUFFER_SIZE + 1);
	if (buffer == NULL)
		return (NULL);
	read_bytes = read(fd, buffer, BUFFER_SIZE);
	if (read_bytes == 0)
		return (free(buffer), NULL);
	if (read_bytes < 0)
		return (free(buffer), free_stash(stash), NULL);
	buffer[read_bytes] = '\0';
	return (buffer);
}

t_list	*append_buffer(t_list **stash, char *buffer)
{
	t_list	*new;
	t_list	*current;

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

int	strcat_untiln(char *dest, char **src)
{
	size_t	i;
	size_t	j;

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
		ft_memmove(*src, *src + j, ft_strlen(*src + j) + 1);
		dest[i] = '\0';
		return (1);
	}
	dest[i] = '\0';
	return (0);
}

char	*strcat_list(t_list **res)
{
	char	*str;
	t_list	*tmp_list;
	size_t	len;

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
	if (str[0] == '\0')
		return (free(str), NULL);
	return (str);
}

// int main(int argc, char **argv)
//{
//    int fd;
//	char *line;
//
//    fd = open(argv[1], O_RDONLY);
//	line = get_next_line(fd);
//    printf("%s", line);
//	free(line);
//	line = get_next_line(fd);
//    printf("%s", line);
//    free(line);
//    close(fd);
//    return (0);
//}
