/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marasolo <marasolo@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 09:31:30 by marasolo          #+#    #+#             */
/*   Updated: 2026/03/05 08:36:15 by marasolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "get_next_line.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strjoin(const char	*s1, const char	*s2)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	return (str);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s != '\0')
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (NULL);
}

void	ft_bzero(void *s, size_t n)
{
	size_t	dest;

	dest = 0;
	while (dest < n)
	{
		*(unsigned char *)(s + dest) = 0;
		dest++;
	}
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*index;
	size_t	total;

	total = nmemb * size;
	if (size != 0 && nmemb > (SIZE_MAX / size))
		return (NULL);
	index = malloc(total);
	if (!index)
		return (NULL);
	ft_bzero(index, total);
	return (index);
}
