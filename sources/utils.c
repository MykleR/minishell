/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrouves <mrouves@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 19:46:48 by mrouves           #+#    #+#             */
/*   Updated: 2025/02/21 15:14:38 by mrouves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	error_print(t_error_type e)
{
	const char	*errors = E_MSG_OK E_MSG_LEX E_MSG_AST E_MSG_CLOSE \
		E_MSG_WRITE E_MSG_FORK E_MSG_OPEN E_MSG_PIPE E_MSG_DUP2 E_MSG_SIG;
	const char	*msg;

	msg = errors;
	msg += (int)e;
	write(2, msg, ft_strlen(msg));
}

int	sig_handle(int num, t_sig_callb handler, t_sig_type type)
{
	t_sigaction	sig;

	sigemptyset(&sig.sa_mask);
	sig.sa_sigaction = handler.h_complex;
	sig.sa_handler = handler.h_simple;
	sig.sa_flags = SA_RESTART;
	if (type == SIG_IGNORE || !handler.h_simple)
		sig.sa_handler = SIG_IGN;
	else if (type == SIG_RESTORE)
		sig.sa_flags = SA_RESETHAND;
	else if (type == SIG_COMPLEX)
		sig.sa_flags |= SA_SIGINFO;
	if (sigaction(num, &sig, 0) == -1)
		return (E_SYS_SIG);
	return (E_OK);
}
