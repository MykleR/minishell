/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mykle <mykle@42angouleme.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 17:05:03 by mykle             #+#    #+#             */
/*   Updated: 2025/03/19 13:23:50 by mrouves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	rl_nl(int num)
{
	g_sigint = 128 + num;
	write(STDERR_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

int	sig_set(void)
{
	return (signal(SIGINT, rl_nl) == SIG_ERR
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

int	sig_exit(void)
{
	return (signal(SIGINT, exit) == SIG_ERR
		|| signal(SIGQUIT, SIG_IGN) == SIG_ERR);
}
