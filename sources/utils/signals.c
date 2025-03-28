/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mykle <mykle@42angouleme.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 17:05:03 by mykle             #+#    #+#             */
/*   Updated: 2025/03/26 12:58:08 by mykle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	sig_callb_newline(int num)
{
	g_sigint = 128 + num;
	write(STDERR_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	sig_callb_exit(int num)
{
	exit(128 + num);
}

int	sig_set(void (*callb)(int num))
{
	return (signal(SIGINT, callb) == SIG_ERR
		|| signal(SIGQUIT, SIG_IGN) == SIG_ERR);
}

int	sig_default(void)
{
	return (signal(SIGINT, SIG_DFL) == SIG_ERR
		|| signal(SIGQUIT, SIG_DFL) == SIG_ERR);
}

int	sig_ignore(void)
{
	return (signal(SIGINT, SIG_IGN) == SIG_ERR
		|| signal(SIGQUIT, SIG_IGN) == SIG_ERR);
}
