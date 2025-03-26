/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrouves <mrouves@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 22:33:33 by mrouves           #+#    #+#             */
/*   Updated: 2025/03/26 12:43:47 by mykle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <execution.h>

static inline pid_t	use_tube(int tube[2], t_access mode,
						t_ast *todo, t_hmap *env)
{
	pid_t	pid;

	pid = fork();
	if (!pid)
	{
		cached_close(tube[mode ^ 1]);
		exit(redirection(tube[mode], mode, todo, env));
	}
	cached_close(tube[mode]);
	return (pid);
}

int	execute_pipe(t_binary_expr *expr, t_hmap *env)
{
	int		tube[2];
	pid_t	lpid;
	pid_t	rpid;

	if (!expr || cached_pipe(tube) == -1)
		return (EXIT_FAILURE);
	lpid = use_tube(tube, WRITE, expr->left, env);
	rpid = use_tube(tube, READ, expr->right, env);
	query_child(lpid);
	return (query_child(rpid));
}
