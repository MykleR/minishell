/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrouves <mrouves@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 13:24:06 by mrouves           #+#    #+#             */
/*   Updated: 2025/01/15 12:42:10 by thomarna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <libft.h>
# include <signal.h>
# include <stdarg.h>

typedef struct sigaction	t_sigaction;

typedef enum e_sig_type
{
	SIG_SIMPLE,
	SIG_COMPLEX
}	t_sig_type;

typedef union u_sig_handler
{
	void	(*h_simple)(int);
	void	(*h_complex)(int, siginfo_t *, void *);
}	t_sig_handler;

bool	sigs_add_handler(t_sig_handler handler,
			t_sig_type type, int nb_sigs, ...);
void	run_lexer(const char *input);
#endif
