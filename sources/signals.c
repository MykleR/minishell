/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrouves <mrouves@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 17:59:59 by mrouves           #+#    #+#             */
/*   Updated: 2025/01/14 19:22:34 by mrouves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static bool	sig_add_handler(t_sig_handler handler, t_sig_type type, int num)
{
	t_sigaction	sig;

	sigemptyset(&sig.sa_mask);
	sig.sa_sigaction = handler.h_complex;
	sig.sa_handler = handler.h_simple;
	sig.sa_flags = SA_RESTART;
	if (type == SIG_COMPLEX)
		sig.sa_flags |= SA_SIGINFO;
	return (sigaction(num, &sig, 0) != -1);
}

bool	sigs_add_handler(t_sig_handler handler,
			t_sig_type type, int nb_sig, ...)
{
	va_list	args;
	bool	success;

	if (__builtin_expect(!handler.h_simple, 0))
		return (false);
	success = true;
	va_start(args, nb_sig);
	while (nb_sig-- && success)
		success &= sig_add_handler(handler, type, va_arg(args, int));
	va_end(args);
	return (success);
}
