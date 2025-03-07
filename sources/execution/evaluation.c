/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrouves <mrouves@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 20:22:39 by mrouves           #+#    #+#             */
/*   Updated: 2025/03/06 16:45:09 by mykle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <execution.h>

int	query_child(pid_t pid)
{
	int	status;

	if (pid < 0)
		return (EXIT_FAILURE);
	status = 0;
	if (waitpid(pid, &status, 0) == -1)
		return (EXIT_FAILURE);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (WTERMSIG(status) + 128);
}

int	evaluate(t_ast *ast, t_hmap *env)
{
	if (!ast)
		return (EXIT_SUCCESS);
	if (ast->type == AST_SUBSHELL)
		return (evaluate(ast->expr.binary.left, env));
	if (ast->type == AST_CMD)
		return (execute_cmd(&ast->expr.cmd, env));
	else if (ast->type == AST_PIPE)
		return (execute_pipe(&ast->expr.binary, env));
	else if (ast->type == AST_AND)
		return (execute_and(&ast->expr.binary, env));
	else if (ast->type == AST_OR)
		return (execute_or(&ast->expr.binary, env));
	else if (ast->type == AST_REDIR)
		return (execute_redir(&ast->expr.redir, env));
	return (EXIT_FAILURE);
}
