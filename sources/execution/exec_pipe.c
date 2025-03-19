/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrouves <mrouves@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 22:33:33 by mrouves           #+#    #+#             */
/*   Updated: 2025/03/19 13:18:23 by mrouves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <execution.h>

static inline pid_t	use_tube(int tube[2], t_access mode,
						t_ast *todo, t_hmap *env)
{
	pid_t	pid;
	int		backup;

	backup = dup(mode);
	safe_dup2(tube[mode], mode);
	close(tube[mode]);
	pid = safe_fork();
	if (!pid)
	{
		close(tube[mode ^ 1]);
		close(backup);
		exit(evaluate(todo, env));
	}
	safe_dup2(backup, mode);
	close(backup);
	return (pid);
}

int	execute_pipe(t_binary_expr *expr, t_hmap *env)
{
	int		tube[2];
	pid_t	lpid;
	pid_t	rpid;

	if (!expr || safe_pipe(tube) == -1)
		return (EXIT_FAILURE);
	lpid = use_tube(tube, WRITE, expr->left, env);
	rpid = use_tube(tube, READ, expr->right, env);
	query_child(lpid);
	return (query_child(rpid));
}
