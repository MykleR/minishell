/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrouves <mrouves@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 13:24:06 by mrouves           #+#    #+#             */
/*   Updated: 2025/01/17 15:47:42 by mykle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <libft.h>
# include <signal.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

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

bool	sig_handle(int num, t_sig_callb handler, t_sig_type type);
void	run_lexer(const char *input);
#endif
