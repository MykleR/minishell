/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrouves <mrouves@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 20:22:39 by mrouves           #+#    #+#             */
/*   Updated: 2025/03/05 22:13:52 by mykle            ###   ########.fr       */
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

int	redirection(int fd_to, int fd_from, t_ast *todo)
{
	int		status;
	int		backup;

	if (fd_to < 0 || fd_from < 0)
		return (EXIT_FAILURE);
	backup = dup(fd_from);
	status = backup != -1 && dup2(fd_to, fd_from) != -1;
	close(fd_to);
	if (!status)
		return (EXIT_FAILURE);
	status = evaluate(todo);
	dup2(backup, fd_from);
	close(backup);
	return (status);
}

int	evaluate(t_ast *ast)
{
	if (!ast)
		return (EXIT_SUCCESS);
	if (ast->type == AST_SUBSHELL)
		return (evaluate(ast->expr.binary.left));
	if (ast->type == AST_CMD)
		return (execute_cmd(&ast->expr.cmd));
	else if (ast->type == AST_PIPE)
		return (execute_pipe(&ast->expr.binary));
	else if (ast->type == AST_AND)
		return (execute_and(&ast->expr.binary));
	else if (ast->type == AST_OR)
		return (execute_or(&ast->expr.binary));
	else if (ast->type == AST_REDIR)
		return (execute_redir(&ast->expr.redir));
	return (EXIT_FAILURE);
}
