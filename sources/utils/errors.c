/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mykle <mykle@42angouleme.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 16:59:51 by mykle             #+#    #+#             */
/*   Updated: 2025/03/05 18:44:58 by mykle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <utils.h>

void	error_print(t_error_type e)
{
	const char	*errors = E_MSG_OK E_MSG_LEX E_MSG_AST E_MSG_CLOSE \
		E_MSG_WRITE E_MSG_FORK E_MSG_OPEN E_MSG_PIPE E_MSG_DUP2 E_MSG_SIG;
	const char	*msg;

	if (e == E_OK)
		return ;
	msg = errors;
	msg += (int)e;
	write(STDERR_FILENO, msg, ft_strlen(msg));
}
