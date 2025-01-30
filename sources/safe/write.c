/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomarna <thomarna@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 10:16:00 by thomarna          #+#    #+#             */
/*   Updated: 2025/01/30 10:20:42 by thomarna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

ssize_t	safe_write(int fd, const void *buffer, size_t count)
{
	ssize_t bytes_write;
	size_t	total_write;

	total_write = 0;
	while (total_write < count)
	{
		bytes_write = write(fd, (const char *)buffer + total_write, count - total_write);
		if (bytes_write == -1)
		{
			if (errno == EINTR)
				continue;
			perror("Error - Can't write\n");
			exit(1);
		}
		total_write += bytes_write;
	}
	return (total_write);
}
