/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_logic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrouves <mrouves@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 23:45:24 by mrouves           #+#    #+#             */
/*   Updated: 2025/03/06 16:37:24 by mykle            ###   ########.fr       */
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
