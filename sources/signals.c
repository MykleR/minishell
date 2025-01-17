/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrouves <mrouves@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 17:59:59 by mrouves           #+#    #+#             */
/*   Updated: 2025/01/17 02:30:47 by mrouves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	sig_handle(int num, t_sig_callb handler, t_sig_type type)
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
	return (sigaction(num, &sig, 0) != -1);
}
