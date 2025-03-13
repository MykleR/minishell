/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_rl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrouves <mrouves@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 11:46:06 by mrouves           #+#    #+#             */
/*   Updated: 2025/03/13 06:22:24 by mrouves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	on_shell_prompt(t_shell *shell, const char *cmd)
{
	if (tokenize(cmd, &shell->tokens))
		return (EXIT_FAILURE);
	if (heredoc_handler(&shell->tokens))
		return (EXIT_FAILURE);
	if (lalr_parse(&shell->parser, &shell->tokens))
		return (EXIT_FAILURE);
	shell->status = evaluate(shell->parser.ast, &shell->env);
	hmap_set(&shell->env, "?", &(char *){ft_itoa(shell->status)});
	ft_dprintf(STDERR_FILENO, "[%d]\n", shell->status);
	return (E_OK);
}

void	rl_shell_prompt(t_shell *shell)
{
	char	*buf;

	buf = readline(rl_readline_name);
	while (buf)
	{
		if (ft_strlen(buf) > 0)
		{
			add_history(buf);
			sig_ignore();
			on_shell_prompt(shell, buf);
			sig_set();
		}
		shell_clear(shell);
		free(buf);
		buf = readline(rl_readline_name);
	}
}
