/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrouves <mrouves@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 19:46:48 by mrouves           #+#    #+#             */
/*   Updated: 2025/01/29 21:07:34 by mrouves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	error_print(t_error_type e)
{
	const char	*msg;

	msg = ERROR_MSGS;
	msg += (int)e;
	write(2, msg, ft_strlen(msg));
}

void	rl_shell_nl(int num)
{
	(void) num;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	rl_shell_prompt(t_shell *shell, const char *prompt,
			int (*callback)(t_shell *shell))
{
	char	*buf;

	buf = readline(prompt);
	while (buf)
	{
		shell->cmd = ft_strdup(buf);
		free(buf);
		if (ft_strlen(shell->cmd) > 0)
			add_history(shell->cmd);
		error_print(callback(shell));
		alloc_f((void *)shell->cmd);
		buf = readline(prompt);
	}
}

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
	if (sigaction(num, &sig, 0) == -1)
		return (E_SYS_SIG);
	return (E_OK);
}


