/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrouves <mrouves@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 13:23:24 by mrouves           #+#    #+#             */
/*   Updated: 2025/03/26 13:31:22 by mykle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	g_sigint = 0;

__attribute__((destructor))
static void	__cleanup(void)
{
	rl_clear_history();
}

__attribute__((constructor))
static void	__construct(void)
{
	rl_outstream = stderr;
	rl_readline_name = "";
	if (isatty(STDIN_FILENO))
	{
		rl_readline_name = SHELL_PROMPT;
		ft_dprintf(STDERR_FILENO, "%s", SHELL_BANNER);
	}
	else
		rl_prep_term_function = 0;
}

int	main(int __attribute_maybe_unused__(ac),
		char **__attribute_maybe_unused__(av),
		const char **env)
{
	static t_shell	shell = {0};

	shell_init(&shell, env);
	shell_process(&shell);
	shell_destroy(&shell);
	if (isatty(STDIN_FILENO))
		ft_dprintf(STDERR_FILENO, "exit\n");
	return (shell.status);
}
