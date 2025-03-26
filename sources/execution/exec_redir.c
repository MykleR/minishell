/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrouves <mrouves@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 23:26:07 by mrouves           #+#    #+#             */
/*   Updated: 2025/03/26 12:31:20 by mykle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <execution.h>

static inline int	get_fd(t_redir_type type)
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

int	redirection(int ofd, int nfd, t_ast *todo, t_hmap *env)
{
	int		status;
	int		backup;

	if (ofd < 0 || nfd < 0)
		return (EXIT_FAILURE);
	status = EXIT_FAILURE;
	backup = cached_dup(nfd);
	if (backup != -1 && cached_dup2(ofd, nfd) != -1)
		status = evaluate(todo, env);
	cached_close(ofd);
	cached_dup2(backup, nfd);
	cached_close(backup);
	return (status);
}

int	execute_redir(t_redir_expr *expr, t_hmap *env)
{
	t_collection	expanded;

	if (!expr || !expr->file)
		return (EXIT_FAILURE);
	if (expand_simple(expr->file, &expanded, env) != 1)
	{
		collection_destroy(&expanded);
		return (error(E_AMBIGUOUS, expr->file));
	}
	alloc_f(expr->file);
	expr->file = ft_strdup(*(char **)expanded.data);
	expr->fd = try_open(expr->file, get_flags(expr->type));
	collection_destroy(&expanded);
	return (redirection(expr->fd, get_fd(expr->type), expr->next, env));
}
