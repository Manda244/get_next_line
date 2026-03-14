/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marasolo <marasolo@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 15:00:08 by marasolo          #+#    #+#             */
/*   Updated: 2026/03/14 15:08:05 by marasolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_line(char **rest)
{
	char	*line;
	char	*tmp;
	char	*n_line;

	if (!*rest || **rest == '\0')
	{
		free(*rest);
		*rest = NULL;
		return (NULL);
	}
	tmp = NULL;
	n_line = ft_strchr(*rest, '\n');
	if (n_line)
	{
		line = ft_substr(*rest, 0, n_line - *rest + 1);
		tmp = ft_strdup(n_line + 1);
	}
	else
		line = ft_strdup(*rest);
	free(*rest);
	*rest = tmp;
	return (line);
}

static char	*read_line(int fd, char *rest)
{
	char	*buffer;
	char	*tmp;
	int		count;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	count = 1;
	while (count > 0 && !ft_strchr(rest, '\n'))
	{
		count = read(fd, buffer, BUFFER_SIZE);
		if (count == -1)
		{
			free(buffer);
			free (rest);
			return (NULL);
		}
		buffer[count] = '\0';
		tmp = ft_strjoin(rest, buffer);
		free(rest);
		rest = tmp;
	}
	free(buffer);
	return (rest);
}

char	*get_next_line(int fd)
{
	static char	*rest;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	rest = read_line(fd, rest);
	line = ft_line(&rest);
	return (line);
}
