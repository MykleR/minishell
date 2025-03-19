/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_logic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrouves <mrouves@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 23:45:24 by mrouves           #+#    #+#             */
/*   Updated: 2025/03/19 05:37:16 by mrouves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <execution.h>

int	execute_and(t_binary_expr *expr, t_hmap *env)
{
	int	status;

	status = evaluate(expr->left, env);
	if (status == EXIT_SUCCESS)
		status = evaluate(expr->right, env);
	return (status);
}

int	execute_or(t_binary_expr *expr, t_hmap *env)
{
	int	status;

	status = evaluate(expr->left, env);
	if (status != EXIT_SUCCESS)
		status = evaluate(expr->right, env);
	return (status);
}

int	execute_subshell(t_binary_expr *expr, t_hmap *env)
{
	pid_t	pid;

	pid = safe_fork();
	if (pid)
		return (query_child(pid));
	exit(evaluate(expr->left, env));
}
