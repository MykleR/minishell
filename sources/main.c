/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrouves <mrouves@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 13:23:24 by mrouves           #+#    #+#             */
/*   Updated: 2025/03/04 00:31:29 by mrouves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

__attribute__((destructor))
static void	__cleanup(void)
{
	rl_clear_history();
}

int	main(void)
{
	static t_shell	shell = {0};

	if (sig_handle(SIGINT, (t_sig_callb)rl_shell_nl, SIG_SIMPLE)
		|| sig_handle(SIGQUIT, (t_sig_callb){0}, SIG_IGNORE))
	{
		error_print(E_SYS_SIG);
		return (EXIT_FAILURE);
	}
	if (shell_init(&shell, SHELL_PROMPT))
		rl_shell_prompt(&shell);
	shell_destroy(&shell);
	ft_printf("exit\n");
	return (EXIT_SUCCESS);
}
