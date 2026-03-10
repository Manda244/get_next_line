/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@local>                           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 00:00:00 by user               #+#    #+#             */
/*   Updated: 2026/03/10 00:00:00 by user              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "get_next_line.h"

int	main(void)
{
	int     fd;
	int     read_fd;
	char    *line;

	fd = open("test.txt", O_RDONLY);
	if (fd == -1)
		read_fd = STDIN_FILENO;
	else
		read_fd = fd;
	while ((line = get_next_line(read_fd)) != NULL)
	{
		/* get_next_line retourne la ligne (avec le '\n' si présent) */
		printf("%s", line);
		free(line);
	}
	if (fd != -1)
		close(fd);
	return (0);
}

