/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomarna <thomarna@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 09:50:45 by thomarna          #+#    #+#             */
/*   Updated: 2025/01/30 10:14:33 by thomarna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

ssize_t	safe_read(int fd, void *buffer, size_t count)
{
	ssize_t	bytes_read;
	size_t	total_read;

	total_read = 0;
	while (total_read < count)
	{
		bytes_read = read(fd, (char *)buffer + total_read, count - total_read);
		if (bytes_read == -1)
		{
			if (errno == EINTR)
				continue ;
			perror("Error - Can't read file\n");
			exit(1);
		}
		if (bytes_read == 0)
			break ;
		total_read += bytes_read;
	}
	return (total_read);
}
