/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrouves <mrouves@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 23:26:07 by mrouves           #+#    #+#             */
/*   Updated: 2025/03/03 23:43:24 by mrouves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <execution.h>

static int	get_fd(t_redir_type type)
{
	if (type == REDIR_IN)
		return (STDIN_FILENO);
	return (STDOUT_FILENO);
}

static int	get_flags(t_redir_type type)
{
	if (type == REDIR_IN)
		return (O_RDONLY);
	if (type == REDIR_OUT)
		return (O_WRONLY | O_CREAT | O_TRUNC);
	if (type == REDIR_APP)
		return (O_WRONLY | O_CREAT | O_APPEND);
	return (0);
}

int	execute_redir(t_redir_expr *expr)
{
	t_redir	redir;
	int		status;

	if (__builtin_expect(!expr || !expr->next || !expr->file, 0))
		return (EXIT_FAILURE);
	expr->fd = open(expr->file, get_flags(expr->type), 0666);
	if (__builtin_expect(expr->fd == -1
		|| !make_redir(&redir, expr->fd, get_fd(expr->type)), 0))
		return (EXIT_FAILURE);
	close(expr->fd);
	status = evaluate(expr->next);
	if (!restore_redir(&redir))
		return (EXIT_FAILURE);
	return (status);
}
