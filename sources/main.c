/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrouves <mrouves@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 13:23:24 by mrouves           #+#    #+#             */
/*   Updated: 2025/03/18 22:31:54 by mrouves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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

int	main(int ac, const char **av, const char **env)
{
	static t_shell	shell = {0};

	(void)ac;
	(void)av;
	if (shell_init(&shell, env) == E_OK)
		shell_readline(&shell);
	shell_destroy(&shell);
	if (isatty(STDIN_FILENO))
		ft_dprintf(STDERR_FILENO, "exit\n");
	return (shell.status);
}
