/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marasolo <marasolo@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 11:33:27 by marasolo          #+#    #+#             */
/*   Updated: 2026/03/10 09:26:00 by marasolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// join and free
char	*ft_free(char *buffer, char *buf)
{
	char	*temps;

	temps = ft_strjoin(buffer, buf);
	free(buffer);
	return (temps);
}

//take line for return
char	*ft_line(char *buffer, char sign)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] && buffer[i] != sign)
		i++;
	line = ft_calloc(i + 2, sizeof(char));
	j = 0;
	while (buffer[i] && buffer[i] != sign)
	{
		line[j++] = buffer[i++];
	}
	if (buffer[i] && buffer[i] == sign)
		line[i++] = sign;
	return (line);
}

// delet lin find
char	*ft_next(char *buffer, char sign)
{
	int		i;
	int		j;
	char	*line;

	i = 0; //find lin of first lin
	while (buffer[i] && buffer[i] != sign)
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	//line of file - line of firstline + 1
	line = ft_calloc((ft_strlen(buffer) - i + 1), sizeof(char));
	j = 0;
	// line == buffer
	while (buffer[i])
	{
		line[j++] = buffer[i++];
	}
	free(buffer);
	return (line);
}

char	*read_line(int fd, char *res, char sign)
{
	char	*buffer;
	int		count;
	
	//malloc if res dont exist 
	if (!res)
		res = ft_calloc(1, 1);
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	count = 1;
	while (count > 0)
	{
		// while not of read
		count = read(fd, buffer, BUFFER_SIZE);
		if (count == -1)
		{
			free(buffer);
			return (NULL);
		}
		// 0 to end for liks
		buffer[count] = 0;
		// join and free
		res = ft_free(res, buffer);
		// quit if \n find
		if (ft_strchr(buffer, sign))
			break;
	}
	free(buffer);
	return (res);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;
	char		sign;
	
	sign = '\n';
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	buffer = read_line(fd, buffer, sign);
	if (!buffer)
		return (NULL);
	line = ft_line(buffer, sign);
	buffer = ft_next(buffer, sign);
	return (line);
}
