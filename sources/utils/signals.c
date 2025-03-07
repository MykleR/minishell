/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mykle <mykle@42angouleme.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 17:05:03 by mykle             #+#    #+#             */
/*   Updated: 2025/03/07 02:58:54 by mykle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <utils.h>

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
	if (sigaction(num, &sig, 0) == E_ERROR)
		return (error(E_ERROR, "sigaction"));
	return (E_OK);
}
