/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mykle <mykle@42angouleme.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 17:04:54 by mykle             #+#    #+#             */
/*   Updated: 2025/03/05 18:40:58 by mykle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <utils.h>

int	safe_open(const char *filename, int mode)
{
	int	fd;

	fd = open(filename, mode, 0644);
	if (fd == -1)
		ft_dprintf(STDERR_FILENO, "%s: %s\n", filename, strerror(errno));
	return (fd);
}

int	safe_fork(void)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		ft_dprintf(STDERR_FILENO, "fork: %s\n", strerror(errno));
	return (pid);
}
