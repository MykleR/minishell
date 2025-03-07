/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrouves <mrouves@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 23:26:07 by mrouves           #+#    #+#             */
/*   Updated: 2025/03/07 03:56:39 by mykle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <execution.h>

static inline int	get_fd_from(t_redir_type type)
{
	if (type == REDIR_IN)
		return (STDIN_FILENO);
	return (STDOUT_FILENO);
}

static inline int	get_flags(t_redir_type type)
{
	if (type == REDIR_OUT)
		return (O_WRONLY | O_CREAT | O_TRUNC);
	if (type == REDIR_APP)
		return (O_WRONLY | O_CREAT | O_APPEND);
	return (O_RDONLY);
}

int	redirection(int fd_to, int fd_from, t_ast *todo, t_hmap *env)
{
	int		status;
	int		backup;

	if (fd_to < 0 || fd_from < 0)
		return (EXIT_FAILURE);
	backup = dup(fd_from);
	status = backup != -1 && safe_dup2(fd_to, fd_from) != -1;
	safe_close(fd_to);
	if (!status)
		return (EXIT_FAILURE);
	status = evaluate(todo, env);
	safe_dup2(backup, fd_from);
	safe_close(backup);
	return (status);
}

int	execute_redir(t_redir_expr *expr, t_hmap *env)
{
	if (!expr || !expr->file)
		return (EXIT_FAILURE);
	expr->fd = safe_open(expr->file, get_flags(expr->type));
	return (redirection(expr->fd, get_fd_from(expr->type), expr->next, env));
}
