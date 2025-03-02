/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomarna <thomarna@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 16:02:59 by thomarna          #+#    #+#             */
/*   Updated: 2025/03/02 14:43:03 by thomarna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "proto.h"
#include <sys/wait.h>

// Fonctions utiles Gestion multi pipe (Ouverture multiple Pid)
void	multi_pipe(int *pid, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		waitpid(pid[i], NULL, 0);
		i++;
	}
}

void	pipex(t_pipe *tpipe, int *pid, int fd[2][2])
{
	int	i;

	i = 0;
	while (i < tpipe->size)
	{
		if (pipe(fd[i % 2]) < 0)
			// err0r();
			pid[i] = fork();
		if (pid[i] == 0)
		{
			// GEstion de pipe (Dupe2 & close fd[])
			// execve func ??
			return ;
		}
		// close_pipe func ??
		multi_pipe(pid, tpipe->size);
		i++;
	}
}
