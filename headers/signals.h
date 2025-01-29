/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrouves <mrouves@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 16:56:20 by mrouves           #+#    #+#             */
/*   Updated: 2025/01/29 19:32:11 by mrouves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include <signal.h>

typedef struct sigaction	t_sigaction;

typedef enum e_sig_type
{
	SIG_IGNORE,
	SIG_RESTORE,
	SIG_SIMPLE,
	SIG_COMPLEX
}	t_sig_type;

typedef union u_sig_callb
{
	void		(*h_simple)(int);
	void		(*h_complex)(int, siginfo_t *, void *);
}	t_sig_callb;

int	sig_handle(int num, t_sig_callb handler, t_sig_type type);

#endif
