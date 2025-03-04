/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrouves <mrouves@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 22:33:33 by mrouves           #+#    #+#             */
/*   Updated: 2025/03/03 23:53:52 by mrouves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <execution.h>

static pid_t	use_pipe(int tube[2], t_access mode, int target, t_ast *todo)
{
	pid_t	pid;
	int		status;
	t_redir	redir;

	pid = fork();
	if (__builtin_expect(pid == -1, 0))
		exit(EXIT_FAILURE);
	if(pid == 0)
	{
		if (!make_redir(&redir, tube[mode], target))
			exit(EXIT_FAILURE);
		close(tube[W]);
		close(tube[R]);
		status = evaluate(todo);
		if (!restore_redir(&redir))
			exit(EXIT_FAILURE);
		exit(status);
	}
	return (pid);
}

int	execute_pipe(t_binary_expr *expr)
{
	int		tube[2];
	pid_t	lpid;
	pid_t	rpid;

	if(__builtin_expect(!expr || pipe(tube) == -1, 0 ))
		return (1);
	lpid = use_pipe(tube, W, STDOUT_FILENO, expr->left);
	rpid = use_pipe(tube, R, STDIN_FILENO, expr->right);
	close(tube[R]);
	close(tube[W]);
	query_child(lpid);
	return (query_child(rpid));
}
