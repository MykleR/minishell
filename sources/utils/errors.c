/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mykle <mykle@42angouleme.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 16:59:51 by mykle             #+#    #+#             */
/*   Updated: 2025/03/07 03:32:41 by mykle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <utils.h>

int	error(t_error_type e, ...)
{
	const char	*errors = E_MSG_OK E_MSG_LEX E_MSG_AST E_MSG_IS_DIR \
		E_MSG_NOFILE E_MSG_OPEN E_MSG_TOO_MANY E_MSG_NOCMD E_MSG_NOENV \
		E_MSG_NUMERIC;
	const char	*msg;
	va_list		args;

	if (e == E_OK)
		return (e);
	va_start(args, e);
	msg = errors;
	msg += (int)e;
	if (e == E_ERROR)
	{
		ft_vdprintf(STDERR_FILENO, "%s: ", args);
		ft_dprintf(STDERR_FILENO, "%s\n", strerror(errno));
	}
	else
		ft_vdprintf(STDERR_FILENO, msg, args);
	va_end(args);
	return (EXIT_FAILURE);
}
