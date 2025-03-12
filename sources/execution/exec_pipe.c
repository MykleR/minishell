/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrouves <mrouves@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 22:33:33 by mrouves           #+#    #+#             */
/*   Updated: 2025/03/12 01:41:29 by mrouves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <execution.h>

static inline int	use_tube(int tube[2], t_access mode,
						t_ast *todo, t_hmap *env)
{
	safe_close(tube[mode ^ 1]);
	return (redirection(tube[mode], mode, todo, env));
}

int	execute_pipe(t_binary_expr *expr, t_hmap *env)
{
	int		tube[2];
	pid_t	lpid;
	int		status;

	if (!expr || safe_pipe(tube) == -1)
		return (EXIT_FAILURE);
	lpid = safe_fork();
	if (!lpid)
		exit(use_tube(tube, WRITE, expr->left, env));
	status = use_tube(tube, READ, expr->right, env);
	query_child(lpid);
	return (status);
}
