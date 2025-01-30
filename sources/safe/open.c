/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomarna <thomarna@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 09:45:06 by thomarna          #+#    #+#             */
/*   Updated: 2025/01/30 14:40:20 by thomarna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int	safe_open(const char *filename, int flags)
{
	int	fd;

	fd = open(filename, flags);
	if (fd == -1)
	{
		perror("Error - Can't open file\n");
		exit(1);
	}
	return (fd);
}
