/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_rl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrouves <mrouves@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 11:46:06 by mrouves           #+#    #+#             */
/*   Updated: 2025/02/24 20:33:50 by mrouves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	on_shell_prompt(t_shell *shell)
{
	if (tokenize(shell->cmd, &shell->tokens))
		return (E_PARSE_LEX);
	return (lalr_parse(&shell->parser, &shell->tokens));
}

void	rl_shell_nl(int num)
{
	(void) num;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	rl_shell_prompt(t_shell *shell)
{
	char	*buf;

	buf = readline(shell->prompt);
	while (buf)
	{
		shell->cmd = ft_strdup(buf);
		free(buf);
		if (ft_strlen(shell->cmd) > 0)
		{
			add_history(shell->cmd);
			error_print(on_shell_prompt(shell));
		}
		shell_clear(shell);
		buf = readline(shell->prompt);
	}
}
