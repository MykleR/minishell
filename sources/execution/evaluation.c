/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrouves <mrouves@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 20:22:39 by mrouves           #+#    #+#             */
/*   Updated: 2025/03/04 00:31:52 by mrouves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <execution.h>

int	query_child(pid_t pid)
{
	int	status;

	status = 0;
	if (waitpid(pid, &status, 0) == -1) 
		return (EXIT_FAILURE);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (WTERMSIG(status) + 128);
}

int	make_redir(t_redir *redir, int fd, int target)
{
	redir->fd = target;
	redir->backup = dup(target);
	return (redir->backup != -1 && dup2(fd, target) != -1);
}

int	restore_redir(t_redir *redir)
{
	int	status;

	status = dup2(redir->backup, redir->fd);
	status = status != -1 && close(redir->backup) != -1;
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
