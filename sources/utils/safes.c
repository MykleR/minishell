/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mykle <mykle@42angouleme.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 17:04:54 by mykle             #+#    #+#             */
/*   Updated: 2025/03/07 16:29:54 by mrouves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <utils.h>

int	safe_open(const char *filename, int mode)
{
	int	fd;

	fd = open(filename, mode, 0644);
	if (fd == E_ERROR)
		error(E_OPEN, "open", filename, strerror(errno));
	return (fd);
}

int	safe_fork(void)
{
	int	pid;

	pid = fork();
	if (pid == E_ERROR)
		error(E_ERROR, "fork");
	return (pid);
}

int safe_pipe(int pipefd[2])
{
	int	ret;

	ret = pipe(pipefd);
	if (ret == E_ERROR)
		error(E_ERROR, "pipe");
	return (ret);
}

int	safe_close(int fd)
{
	int	ret;

	ret = close(fd);
	if (ret == E_ERROR)
		error(E_ERROR, "close");
	return (ret);
}

int	safe_dup2(int oldfd, int newfd)
{
	int	ret;

	ret = dup2(oldfd, newfd);
	if (ret == E_ERROR)
		error(E_ERROR, "dup2");
	return (ret);
}
