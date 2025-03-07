/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrouves <mrouves@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 22:33:33 by mrouves           #+#    #+#             */
/*   Updated: 2025/03/07 03:07:36 by mykle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <execution.h>

static inline pid_t	use_tube(int tube[2], t_access mode,
						t_ast *todo, t_hmap *env)
{
	pid_t	pid;

	pid = safe_fork();
	if (pid == 0)
	{
		safe_close(tube[mode ^ 1]);
		exit(redirection(tube[mode], mode, todo, env));
	}
	return (pid);
}

int	execute_pipe(t_binary_expr *expr, t_hmap *env)
{
	int		tube[2];
	pid_t	lpid;
	pid_t	rpid;

	if (!expr || safe_pipe(tube) == -1)
		return (EXIT_FAILURE);
	rpid = use_tube(tube, READ, expr->right, env);
	lpid = use_tube(tube, WRITE, expr->left, env);
	safe_close(tube[READ]);
	safe_close(tube[WRITE]);
	query_child(lpid);
	return (query_child(rpid));
}
