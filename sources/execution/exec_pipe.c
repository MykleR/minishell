/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrouves <mrouves@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 22:33:33 by mrouves           #+#    #+#             */
/*   Updated: 2025/03/06 01:17:00 by mykle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <execution.h>

static inline pid_t	use_tube(int tube[2], int fd, t_access mode, t_ast *todo)
{
	pid_t	pid;

	pid = safe_fork();
	if (pid == 0)
	{
		close(tube[mode ^ 1]);
		exit(redirection(tube[mode], fd, todo));
	}
	return (pid);
}

int	execute_pipe(t_binary_expr *expr)
{
	int		tube[2];
	pid_t	lpid;
	pid_t	rpid;

	if (!expr || pipe(tube) == -1)
		return (EXIT_FAILURE);
	rpid = use_tube(tube, STDIN_FILENO, READ, expr->right);
	lpid = use_tube(tube, STDOUT_FILENO, WRITE, expr->left);
	close(tube[READ]);
	close(tube[WRITE]);
	query_child(lpid);
	return (query_child(rpid));
}
