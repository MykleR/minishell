/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_logic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrouves <mrouves@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 23:45:24 by mrouves           #+#    #+#             */
/*   Updated: 2025/03/06 01:17:14 by mykle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <execution.h>

int	execute_and(t_binary_expr *expr)
{
	int	status;

	status = evaluate(expr->left);
	if (status == EXIT_SUCCESS)
		status = evaluate(expr->right);
	return (status);
}

int	execute_or(t_binary_expr *expr)
{
	int	status;

	status = evaluate(expr->left);
	if (status != EXIT_SUCCESS)
		status = evaluate(expr->right);
	return (status);
}
