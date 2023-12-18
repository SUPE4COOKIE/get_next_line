/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwojtasi <mwojtasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 08:19:47 by mwojtasi          #+#    #+#             */
/*   Updated: 2023/12/18 17:17:51 by mwojtasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	free_stash(t_list **stash)
{
	t_list	*tmp;

	while (*stash)
	{
		tmp = (*stash)->next;
		free((*stash)->str);
		free(*stash);
		*stash = tmp;
	}
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

size_t	ft_strlen(const char *s)
{
	size_t	count;

	count = 0;
	while (s[count])
		count++;
	return (count);
}

int	is_line(char *buffer)
{
	size_t	i;

	i = 0;
	while (i < BUFFER_SIZE && buffer[i])
	{
		if (buffer[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

size_t	str_list_len(t_list *list)
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
